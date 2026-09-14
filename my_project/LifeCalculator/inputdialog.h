#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QMessageBox>

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);

    int getYears() const;
    double getHoursPerDay() const;
    
    void setYears(int years);
    void setHoursPerDay(double hours);

private slots:
    void validateAndAccept();

private:
    QLineEdit *yearsLineEdit;
    QLineEdit *hoursLineEdit;
};

#endif // INPUTDIALOG_H