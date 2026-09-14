#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent)
{
    // Создаем модель
    model = new CalculatorModel(this);
    
    // Подключаем сигналы модели к слотам представления
    connect(model, &CalculatorModel::calculationReady, 
            this, &MainWindow::onCalculationReady);
    connect(model, &CalculatorModel::errorOccurred, 
            this, &MainWindow::onErrorOccurred);
    
    // Создаем центральный виджет
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Создаем вертикальный компоновщик
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    // Кнопка "Ввести данные"
    inputButton = new QPushButton("Ввести данные", this);
    inputButton->setFixedHeight(40);
    layout->addWidget(inputButton);
    
    // Метка для результатов
    resultLabel = new QLabel("Нажмите 'Ввести данные' для расчета", this);
    resultLabel->setWordWrap(true);
    resultLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    resultLabel->setStyleSheet("QLabel { font-size: 12px; }");
    layout->addWidget(resultLabel);
    layout->addStretch();
    
    // Настройка окна
    setWindowTitle("Калькулятор Жизни");
    resize(500, 400);
    
    // Подключаем сигнал кнопки к слоту
    connect(inputButton, &QPushButton::clicked, 
            this, &MainWindow::onInputDataClicked);
}

MainWindow::~MainWindow() {}

void MainWindow::onInputDataClicked()
{
    InputDialog dialog(this);
    
    // Восстанавливаем последние значения из модели
    if (model->years() > 0) {
        dialog.setYears(model->years());
    }
    if (model->hoursPerDay() > 0) {
        dialog.setHoursPerDay(model->hoursPerDay());
    }
    
    if (dialog.exec() == QDialog::Accepted) {
        // Обновляем модель (Model получает данные)
        model->setYears(dialog.getYears());
        model->setHoursPerDay(dialog.getHoursPerDay());
        
        // Запускаем расчет через модель
        model->calculate();
    }
}

void MainWindow::onCalculationReady(const CalculatorModel::CalculationResults &results)
{
    // View обновляется на основе данных из Model
    QString resultText = QString(
        "<b>Результаты расчета:</b><br><br>"
        " Всего часов за компьютером: <b>%1 ч.</b><br>"
        " Всего суток: <b>%2 дн.</b><br>"
        " Пробег курсора: <b>%3 км</b><br>"
        " Количество кликов: <b>%4</b><br>"
        " Количество нажатий клавиш: <b>%5</b>"
    )
    .arg(results.totalHours, 0, 'f', 1)
    .arg(results.totalDays, 0, 'f', 1)
    .arg(results.cursorDistanceKm, 0, 'f', 1)
    .arg(results.totalClicks)
    .arg(results.totalKeystrokes);
    
    resultLabel->setText(resultText);
}

void MainWindow::onErrorOccurred(const QString &message)
{
    QMessageBox::warning(this, "Ошибка", message);
}