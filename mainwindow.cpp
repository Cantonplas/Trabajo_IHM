#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QDebug>

MainWindow::MainWindow(const Problem &problem, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_currentProblem(problem) // Guardamos el problema recibido
{
    ui->setupUi(this);

    // Configurar Escena
    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);

    // Configurar Grupo de Botones para las respuestas
    m_answerGroup = new QButtonGroup(this);
    m_answerGroup->addButton(ui->radioAns1, 0);
    m_answerGroup->addButton(ui->radioAns2, 1);
    m_answerGroup->addButton(ui->radioAns3, 2);
    m_answerGroup->addButton(ui->radioAns4, 3);

    // Cargar interfaz y mapa
    loadChart();
    setupProblemUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadChart()
{
    // IMPORTANTE: Asegúrate de tener "carta_nautica.jpg" en tu archivo de recursos (resources.qrc)
    // o cambia la ruta a donde tengas la imagen.
    QPixmap chart(":/carta_nautica.jpg");

    if (chart.isNull()) {
        m_scene->addText("Error: No se pudo cargar la imagen de la carta náutica.\nVerifica resources.qrc");
    } else {
        m_scene->addPixmap(chart);
        m_scene->setSceneRect(chart.rect());
        ui->graphicsView->fitInView(m_scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::setupProblemUI()
{
    // Poner el texto del problema
    ui->labelProblemText->setText(m_currentProblem.text());

    // NOTA: Aquí deberías extraer las respuestas reales de tu objeto 'Problem'
    // Como navtypes.h no muestra si Problem tiene respuestas, pongo ejemplos.
    // Si tu clase Problem tiene un método getAnswers(), úsalo aquí.

    /* Ejemplo hipotético si Problem tuviera lista de respuestas:
    auto answers = m_currentProblem.answers();
    if(answers.size() > 0) ui->radioAns1->setText(answers[0].text);
    if(answers.size() > 1) ui->radioAns2->setText(answers[1].text);
    ...
    */

    // Por defecto (si no hay datos de respuestas en la BD):
    ui->radioAns1->setText("12.5 millas");
    ui->radioAns2->setText("10.2 millas");
    ui->radioAns3->setText("15.0 millas");
    ui->radioAns4->setText("9.8 millas");
}

void MainWindow::on_btnCheck_clicked()
{
    int id = m_answerGroup->checkedId();
    if (id == -1) {
        QMessageBox::warning(this, "Atención", "Por favor seleccione una respuesta.");
        return;
    }

    // Lógica de validación
    // Aquí deberías comparar con la respuesta correcta del Problem
    // bool esCorrecta = m_currentProblem.checkAnswer(id);

    // Simulación:
    bool esCorrecta = (id == 0); // Suponemos que la primera es la correcta para probar

    if (esCorrecta) {
        QMessageBox::information(this, "Resultado", "¡Correcto!");
    } else {
        QMessageBox::critical(this, "Resultado", "Incorrecto. Inténtalo de nuevo.");
    }
}

void MainWindow::on_btnZoomIn_clicked()
{
    ui->graphicsView->scale(1.2, 1.2);
}

void MainWindow::on_btnZoomOut_clicked()
{
    ui->graphicsView->scale(1.0/1.2, 1.0/1.2);
}

void MainWindow::on_btnClose_clicked()
{
    this->close();
}
