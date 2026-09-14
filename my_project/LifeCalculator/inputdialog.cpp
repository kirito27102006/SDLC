#include "inputdialog.h"

InputDialog::InputDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Ввод данных");
    setMinimumWidth(350);
    
    // Главный вертикальный layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Форма с полями ввода
    QFormLayout *formLayout = new QFormLayout();
    
    // Поле для лет (обычный QLineEdit)
    yearsLineEdit = new QLineEdit(this);
    yearsLineEdit->setPlaceholderText("Например: 30");
    formLayout->addRow("Количество лет:", yearsLineEdit);
    
    // Поле для часов в день (обычный QLineEdit)
    hoursLineEdit = new QLineEdit(this);
    hoursLineEdit->setPlaceholderText("Например: 8.5");
    formLayout->addRow("Часов в день за ПК:", hoursLineEdit);
    
    mainLayout->addLayout(formLayout);
    
    // Кнопки OK / Cancel
    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    mainLayout->addWidget(buttonBox);
    
    // Подключаем кнопки
    connect(buttonBox, &QDialogButtonBox::accepted, this, &InputDialog::validateAndAccept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

int InputDialog::getYears() const 
{ 
    return yearsLineEdit->text().toInt(); 
}

double InputDialog::getHoursPerDay() const 
{ 
    return hoursLineEdit->text().toDouble(); 
}

void InputDialog::setYears(int years) 
{ 
    yearsLineEdit->setText(QString::number(years)); 
}

void InputDialog::setHoursPerDay(double hours) 
{ 
    hoursLineEdit->setText(QString::number(hours, 'f', 1)); 
}

void InputDialog::validateAndAccept()
{
    // Проверяем, что поля не пустые
    if (yearsLineEdit->text().trimmed().isEmpty() || hoursLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", 
            "Пожалуйста, заполните все поля.");
        return;  // Диалог не закрывается
    }
    
    // Проверяем, что введены числа
    bool yearsOk, hoursOk;
    int years = yearsLineEdit->text().toInt(&yearsOk);
    double hours = hoursLineEdit->text().toDouble(&hoursOk);
    
    if (!yearsOk || !hoursOk) {
        QMessageBox::warning(this, "Ошибка ввода", 
            "Пожалуйста, введите корректные числа.");
        return;  // Диалог не закрывается
    }
    
    // Проверяем диапазоны
    if (years <= 0 || years > 120) {
        QMessageBox::warning(this, "Ошибка ввода", 
            "Количество лет должно быть от 1 до 120.");
        return;  // Диалог не закрывается
    }
    
    if (hours <= 0 || hours > 24) {
        QMessageBox::warning(this, "Ошибка ввода", 
            "Количество часов должно быть от 0.5 до 24.");
        return;  // Диалог не закрывается
    }
    
    // Если всё корректно — закрываем диалог
    accept();
}