/*
 * Author:     Miguel Angel <dumabg@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DATETIMETIPSWIDGET_H
#define DATETIMETIPSWIDGET_H
#include "tipswidget.h"
#include <QTimeZone>
#include <QTimer>

class DatetimeTipsWidget: public TipsWidget
{
    Q_OBJECT
public:
    DatetimeTipsWidget(const bool is24HourFormat);
private slots:
    void oneTimeZone();
    void multipleTimeZones();
private:
    struct UserTimezone {
        QString zoneName;
        QTimeZone timeZone;
    };
    QString m_hourFormat;
    QTimer m_timer;
    QVector<UserTimezone> m_userTimezones;
};

#endif // DATETIMETIPSWIDGET_H
