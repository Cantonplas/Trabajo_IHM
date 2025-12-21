#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QButtonGroup>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QAbstractButton>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "navtypes.h"
#include <QSvgRenderer>
#include "tool.h"
#include <QGraphicsBlurEffect>
#include <QListWidgetItem>
#include "navigation.h"
#include "statsdialog.h"
#include <QMenu>
#include <QDateTime>
#include <QGraphicsEllipseItem>

enum DrawMode {
    NONE,
    POINT_MODE,
    LINE_MODE,
    ARC_MODE,
    TEXT_MODE,
    PROTRACTOR_MODE,
    RULER_MODE,
    ERASER_MODE
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// --- Añadir estos al principio del archivo si no están ---
#include <QtMath>
#include <QPen>

class RulerItem : public QGraphicsPixmapItem {
public:
    RulerItem(const QPixmap &pixmap) : QGraphicsPixmapItem(pixmap), m_rotating(false), m_tempLine(nullptr) {
        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);
        // La regla debe escalar con el mapa
        setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
        setTransformOriginPoint(boundingRect().center());
    }

    QPainterPath shape() const override {
        QPainterPath path;
        path.addRect(boundingRect().adjusted(0, -30, 0, 30));
        return path;
    }

protected:
    bool m_rotating;
    QGraphicsLineItem *m_tempLine;
    QPointF m_drawStartScene;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        // --- BOTÓN DERECHO: EMPEZAR A DIBUJAR ---
        if (event->button() == Qt::RightButton) {
            m_drawStartScene = event->scenePos();
            m_tempLine = new QGraphicsLineItem();

            // Color de la línea (puedes ajustarlo)
            QPen pen(Qt::blue, 2);
            m_tempLine->setPen(pen);
            m_tempLine->setZValue(5); // Por encima de la carta, debajo de la regla

            scene()->addItem(m_tempLine);
            m_tempLine->setLine(QLineF(m_drawStartScene, m_drawStartScene));
            return;
        }

        // --- BOTÓN IZQUIERDO: MOVER O ROTAR ---
        if (event->button() == Qt::LeftButton) {
            qreal x = event->pos().x();
            if (x < pixmap().width() * 0.15 || x > pixmap().width() * 0.85) m_rotating = true;
            else m_rotating = false;
        }
        QGraphicsPixmapItem::mousePressEvent(event);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
        // Lógica de Dibujo Recto siguiendo la Regla
        if (m_tempLine && (event->buttons() & Qt::RightButton)) {
            QPointF currentMouseScene = event->scenePos();

            // Convertimos la rotación a Radianes (Qt usa grados)
            // Usamos el ángulo negativo porque el eje Y en pantalla es invertido
            qreal angleRad = qDegreesToRadians(rotation());

            // Vector del movimiento del ratón desde el inicio
            qreal dx = currentMouseScene.x() - m_drawStartScene.x();
            qreal dy = currentMouseScene.y() - m_drawStartScene.y();

            // PROYECCIÓN MATEMÁTICA: Forzamos que la distancia se aplique
            // solo en la dirección de la regla (cos(a), sin(a))
            qreal projectionDist = dx * qCos(angleRad) + dy * qSin(angleRad);

            QPointF constrainedEndPoint(
                m_drawStartScene.x() + projectionDist * qCos(angleRad),
                m_drawStartScene.y() + projectionDist * qSin(angleRad)
                );

            m_tempLine->setLine(QLineF(m_drawStartScene, constrainedEndPoint));
            return;
        }

        // Lógica de Rotación suave
        if (m_rotating && (event->buttons() & Qt::LeftButton)) {
            QPointF centerInScene = mapToScene(transformOriginPoint());
            QLineF line(centerInScene, event->scenePos());
            setRotation(-line.angle());
        } else {
            QGraphicsPixmapItem::mouseMoveEvent(event);
        }
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
        if (event->button() == Qt::RightButton) {
            m_tempLine = nullptr; // La línea se queda "fijada" en el mapa
        }
        QGraphicsPixmapItem::mouseReleaseEvent(event);
    }
};

// --- EN mainwindow.h ---
#include <QtMath>

class CompassItem : public QGraphicsItem {
public:
    CompassItem(const QPixmap &legPixmap) : m_radius(100), m_isOpening(false) {
        // Creamos las dos patas
        m_leg1 = new QGraphicsPixmapItem(legPixmap, this);
        m_leg2 = new QGraphicsPixmapItem(legPixmap, this);

        // Ajustamos el origen de cada pata al "eje" superior (donde se unen)
        // Asumiendo que el eje está en la parte superior central del SVG
        QPointF hinge(legPixmap.width() / 2, 0);
        m_leg1->setTransformOriginPoint(hinge);
        m_leg2->setTransformOriginPoint(hinge);

        // La pata 1 apunta un poco a la izquierda, la 2 a la derecha
        updateLegs();

        setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
        setFlag(ItemIgnoresTransformations, false); // Para que escale con el zoom
    }

    QRectF boundingRect() const override {
        return childrenBoundingRect().adjusted(-m_radius, -m_radius, m_radius, m_radius);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override {
        // Dibujamos el círculo discontinuo de referencia (distancia guardada)
        QPen pen(Qt::gray, 2, Qt::DashLine);
        painter->setPen(pen);
        painter->drawEllipse(QPointF(m_leg1->transformOriginPoint().x(), 0), m_radius, m_radius);
    }

    // Para que el MainWindow pueda pedirle que pinte el arco definitivo
    void setRadius(qreal r) { m_radius = r; updateLegs(); update(); }
    qreal radius() const { return m_radius; }

protected:
    QGraphicsPixmapItem *m_leg1;
    QGraphicsPixmapItem *m_leg2;
    qreal m_radius;
    bool m_isOpening;

    void updateLegs() {
        // Longitud de la pata (aproximada por el alto del pixmap)
        qreal L = m_leg1->pixmap().height();
        // Calculamos el ángulo necesario para que las puntas se separen la distancia del radio
        qreal angle = qRadiansToDegrees(qAsin(m_radius / (2 * L)));

        m_leg1->setRotation(angle);
        m_leg2->setRotation(-angle);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        // Si pulsas con Shift o cerca de la punta, es para abrir/cerrar
        if (event->modifiers() & Qt::ShiftModifier || event->pos().y() > 50) {
            m_isOpening = true;
        } else {
            m_isOpening = false;
            QGraphicsItem::mousePressEvent(event);
        }
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
        if (m_isOpening) {
            QPointF hinge = mapToScene(m_leg1->transformOriginPoint());
            m_radius = QLineF(hinge, event->scenePos()).length();
            if (m_radius < 10) m_radius = 10;
            updateLegs();
            update();
        } else {
            QGraphicsItem::mouseMoveEvent(event);
        }
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
        m_isOpening = false;
        QGraphicsItem::mouseReleaseEvent(event);
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(User* currentUser, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_btnZoomIn_clicked();
    void on_btnZoomOut_clicked();
    void on_btnClearMap_clicked();
    void on_btnChangeColor_clicked();
    void onToolModeToggled(QAbstractButton *button, bool checked);
    void on_btnShowCoordinates_clicked(bool checked);

    void on_listProblems_itemClicked(QListWidgetItem *item);
    void on_btnRandom_clicked();
    void on_btnCheck_clicked();
    void on_btnClose_clicked();

    void on_btnAvatar_clicked();
    void on_btnLogout_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    Problem m_currentProblem;
    User* m_currentUser;
    QButtonGroup *m_answerGroup;


    int m_sessionHits;
    int m_sessionFaults;
    QDateTime m_sessionStart;
    void saveCurrentSession();
    void updateAvatarUI();

    DrawMode m_currentMode;
    QGraphicsPixmapItem *m_protractorItem = nullptr;
    QGraphicsPixmapItem *m_rulerItem = nullptr;
    QButtonGroup *m_toolGroup = nullptr;
    QPointF m_lineStart;
    QGraphicsLineItem *m_currentLineItem = nullptr;

    void setDrawLineMode(bool enabled);
    void loadChart();
    void setupProblemUI(int index);
    void initSelectionList();

    void showSelectionView();
    void showProblemView();

    bool eventFilter(QObject *watched, QEvent *event) override;
    void setupToolIcons();
    void setupToolModes();
    void showSvgTool(const QString &resourcePath, QGraphicsPixmapItem *&item);

    QPointF m_arcCenter;           // Punto donde pinchaste el centro
    QGraphicsEllipseItem *m_currentArcItem = nullptr;
    CompassItem *m_compassItem = nullptr;

};
