#ifndef CALCULATORMODEL_H
#define CALCULATORMODEL_H

#include <QObject>
#include <QString>

class CalculatorModel : public QObject
{
    Q_OBJECT
    
    // Свойства модели (для доступа извне)
    Q_PROPERTY(int years READ years WRITE setYears NOTIFY yearsChanged)
    Q_PROPERTY(double hoursPerDay READ hoursPerDay WRITE setHoursPerDay NOTIFY hoursPerDayChanged)
    Q_PROPERTY(bool hasData READ hasData NOTIFY hasDataChanged)

public:
    explicit CalculatorModel(QObject *parent = nullptr);
    
    // Геттеры и сеттеры
    int years() const { return m_years; }
    double hoursPerDay() const { return m_hoursPerDay; }
    bool hasData() const { return m_hasData; }
    
    // Структура для хранения результатов
    struct CalculationResults {
        double totalHours;
        double totalDays;
        double cursorDistanceKm;
        long long totalClicks;
        long long totalKeystrokes;
    };

public slots:
    void setYears(int years);
    void setHoursPerDay(double hours);
    void calculate();  // Метод для запуска расчетов

signals:
    void yearsChanged(int years);
    void hoursPerDayChanged(double hours);
    void hasDataChanged(bool hasData);
    void calculationReady(const CalculationResults &results);  // Сигнал с результатами
    void errorOccurred(const QString &message);  // Сигнал об ошибке

private:
    int m_years = 0;
    double m_hoursPerDay = 0.0;
    bool m_hasData = false;
    
    // Константы для расчетов
    static constexpr double CLICKS_PER_HOUR = 1500.0;
    static constexpr double KEYSTROKES_PER_HOUR = 5000.0;
    static constexpr double CURSOR_DISTANCE_PER_HOUR = 0.5;
};

#endif // CALCULATORMODEL_H