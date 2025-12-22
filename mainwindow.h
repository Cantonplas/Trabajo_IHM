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
#include <QColorDialog>

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
    QColor m_currentDrawingColor = Qt::red;

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

};

class RulerItem : public QGraphicsPixmapItem {
public:
    RulerItem(const QPixmap &pixmap, QColor *colorPtr)
        : QGraphicsPixmapItem(pixmap), m_rotating(false), m_tempLine(nullptr), m_globalColorPtr(colorPtr) {
        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);
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
    QColor *m_globalColorPtr; // Guardamos el puntero al color

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if (event->button() == Qt::RightButton) {
            m_drawStartScene = event->scenePos();
            m_tempLine = new QGraphicsLineItem();

            // USAMOS EL COLOR SELECCIONADO: Desreferenciamos el puntero
            QPen pen(*m_globalColorPtr, 2);
            m_tempLine->setPen(pen);
            m_tempLine->setZValue(11); // Un valor alto para que se vea sobre todo

            scene()->addItem(m_tempLine);
            m_tempLine->setLine(QLineF(m_drawStartScene, m_drawStartScene));
            return;
        }

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
