#include "calculatormodel.h"

CalculatorModel::CalculatorModel(QObject *parent)
    : QObject(parent)
{
}

void CalculatorModel::setYears(int years)
{
    if (m_years != years) {
        m_years = years;
        emit yearsChanged(m_years);
        emit hasDataChanged(m_years > 0 && m_hoursPerDay > 0);
    }
}

void CalculatorModel::setHoursPerDay(double hours)
{
    if (m_hoursPerDay != hours) {
        m_hoursPerDay = hours;
        emit hoursPerDayChanged(m_hoursPerDay);
        emit hasDataChanged(m_years > 0 && m_hoursPerDay > 0);
    }
}

void CalculatorModel::calculate()
{
    // Валидация данных
    if (m_years <= 0) {
        emit errorOccurred("Количество лет должно быть больше 0");
        return;
    }
    
    if (m_hoursPerDay <= 0 || m_hoursPerDay > 24) {
        emit errorOccurred("Количество часов должно быть от 0.5 до 24");
        return;
    }
    
    // Выполнение расчетов
    CalculationResults results;
    results.totalHours = m_years * 365.25 * m_hoursPerDay;
    results.totalDays = results.totalHours / 24.0;
    results.cursorDistanceKm = results.totalHours * CURSOR_DISTANCE_PER_HOUR;
    results.totalClicks = static_cast<long long>(results.totalHours * CLICKS_PER_HOUR);
    results.totalKeystrokes = static_cast<long long>(results.totalHours * KEYSTROKES_PER_HOUR);
    
    // Отправка результатов через сигнал
    emit calculationReady(results);
}