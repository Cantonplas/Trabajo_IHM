/********************************************************************************
** Form generated from reading UI file 'statsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATSDIALOG_H
#define UI_STATSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_StatsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDateEdit *dateEditFilter;
    QPushButton *btnFilter;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableStats;
    QLabel *lblSummary;
    QPushButton *btnClose;

    void setupUi(QDialog *StatsDialog)
    {
        if (StatsDialog->objectName().isEmpty())
            StatsDialog->setObjectName("StatsDialog");
        StatsDialog->resize(600, 450);
        verticalLayout = new QVBoxLayout(StatsDialog);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(StatsDialog);
        groupBox->setObjectName("groupBox");
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        dateEditFilter = new QDateEdit(groupBox);
        dateEditFilter->setObjectName("dateEditFilter");
        dateEditFilter->setCalendarPopup(true);

        horizontalLayout->addWidget(dateEditFilter);

        btnFilter = new QPushButton(groupBox);
        btnFilter->setObjectName("btnFilter");

        horizontalLayout->addWidget(btnFilter);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(groupBox);

        tableStats = new QTableWidget(StatsDialog);
        if (tableStats->columnCount() < 3)
            tableStats->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableStats->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableStats->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableStats->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableStats->setObjectName("tableStats");
        tableStats->setAlternatingRowColors(true);
        tableStats->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableStats->setColumnCount(3);

        verticalLayout->addWidget(tableStats);

        lblSummary = new QLabel(StatsDialog);
        lblSummary->setObjectName("lblSummary");
        QFont font;
        font.setBold(true);
        lblSummary->setFont(font);
        lblSummary->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblSummary);

        btnClose = new QPushButton(StatsDialog);
        btnClose->setObjectName("btnClose");

        verticalLayout->addWidget(btnClose);


        retranslateUi(StatsDialog);
        QObject::connect(btnClose, &QPushButton::clicked, StatsDialog, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(StatsDialog);
    } // setupUi

    void retranslateUi(QDialog *StatsDialog)
    {
        StatsDialog->setWindowTitle(QCoreApplication::translate("StatsDialog", "Mis Resultados", nullptr));
        groupBox->setTitle(QCoreApplication::translate("StatsDialog", "Filtrar por fecha", nullptr));
        label->setText(QCoreApplication::translate("StatsDialog", "Mostrar desde:", nullptr));
        dateEditFilter->setDisplayFormat(QCoreApplication::translate("StatsDialog", "dd/MM/yyyy", nullptr));
        btnFilter->setText(QCoreApplication::translate("StatsDialog", "Actualizar", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableStats->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("StatsDialog", "Fecha", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableStats->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("StatsDialog", "Aciertos", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableStats->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("StatsDialog", "Fallos", nullptr));
        lblSummary->setText(QCoreApplication::translate("StatsDialog", "Total: 0 Aciertos, 0 Fallos", nullptr));
        btnClose->setText(QCoreApplication::translate("StatsDialog", "Cerrar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatsDialog: public Ui_StatsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATSDIALOG_H
