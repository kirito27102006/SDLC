#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "calculatormodel.h"
#include "inputdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onInputDataClicked();
    void onCalculationReady(const CalculatorModel::CalculationResults &results);
    void onErrorOccurred(const QString &message);

private:
    QPushButton *inputButton;
    QLabel *resultLabel;
    CalculatorModel *model;
    
    void updateUI();
};

#endif // MAINWINDOW_H