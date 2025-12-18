#include "statsdialog.h"
#include "ui_statsdialog.h"
#include <QDateTime>

StatsDialog::StatsDialog(User* user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatsDialog),
    m_user(user)
{
    ui->setupUi(this);

    ui->tableStats->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->dateEditFilter->setDate(QDate::currentDate().addDays(-7));

    loadStats();
}

StatsDialog::~StatsDialog()
{
    delete ui;
}

void StatsDialog::loadStats()
{
    ui->tableStats->setRowCount(0);

    int totalHits = 0;
    int totalFaults = 0;

    QDate filterDate = ui->dateEditFilter->date();

    const QVector<Session> &sessions = m_user->sessions();

    for(const Session &s : sessions) {
        if (s.timeStamp().date() >= filterDate) {

            int row = ui->tableStats->rowCount();
            ui->tableStats->insertRow(row);

            QTableWidgetItem *itemDate = new QTableWidgetItem(s.timeStamp().toString("dd/MM/yyyy HH:mm"));
            itemDate->setTextAlignment(Qt::AlignCenter);
            ui->tableStats->setItem(row, 0, itemDate);

            QTableWidgetItem *itemHits = new QTableWidgetItem(QString::number(s.hits()));
            itemHits->setTextAlignment(Qt::AlignCenter);
            itemHits->setForeground(Qt::darkGreen);

            QFont fontBold = itemHits->font();
            fontBold.setBold(true);
            itemHits->setFont(fontBold);
            ui->tableStats->setItem(row, 1, itemHits);

            QTableWidgetItem *itemFaults = new QTableWidgetItem(QString::number(s.faults()));
            itemFaults->setTextAlignment(Qt::AlignCenter);
            if (s.faults() > 0) {
                itemFaults->setForeground(Qt::red);
                itemFaults->setFont(fontBold);
            }
            ui->tableStats->setItem(row, 2, itemFaults);

            // Sumar al total
            totalHits += s.hits();
            totalFaults += s.faults();
        }
    }

    ui->lblSummary->setText(QString("Resumen del periodo: %1 Aciertos | %2 Fallos")
                                .arg(totalHits).arg(totalFaults));
}

void StatsDialog::on_btnFilter_clicked()
{
    loadStats();
}
