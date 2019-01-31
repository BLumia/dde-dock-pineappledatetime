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

#include <libdframeworkdbus-2.0/com_deepin_daemon_timedate.h>
#include "datetimetipswidget.h"

DatetimeTipsWidget::DatetimeTipsWidget(const bool is24HourFormat): TipsWidget(Qt::AlignLeft, true),
    m_hourFormat(is24HourFormat ? " HH:mm:ss " : " hh:mm:ss A")
{
    setObjectName("datetime");
    com::deepin::daemon::Timedate timeDate("com.deepin.daemon.Timedate", "/com/deepin/daemon/Timedate", QDBusConnection::sessionBus());
    const QStringList userTimezones = timeDate.userTimezones();
    const int userTimezonesSize = userTimezones.size();
    if (userTimezonesSize > 1) {
        for (int i = 0; i < userTimezonesSize; i++) {
            const QString timeZoneName = userTimezones.at(i);
            QDBusPendingReply<ZoneInfo> pendingReply = timeDate.GetZoneInfo(timeZoneName);
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(pendingReply, this);
            connect(watcher, &QDBusPendingCallWatcher::finished, [this](QDBusPendingCallWatcher* watcher) {
                 QDBusPendingReply<ZoneInfo> reply = *watcher;
                 if (reply.isValid()) {
                     ZoneInfo zoneInfo = reply.value();
                     UserTimezone userTimeZone;
                     const QString zoneName = zoneInfo.getZoneName();
                     userTimeZone.zoneName = zoneName;
                     const QTimeZone timeZone(zoneName.toLatin1());
                     userTimeZone.timeZone = timeZone;
                     // Order time zones by date time
                     const QDateTime currentDateTime = QDateTime::currentDateTime();
                     const int offsetUserTimeZone = currentDateTime.toTimeZone(timeZone).offsetFromUtc();
                     int iUserTimeZones = 0;
                     while (iUserTimeZones < m_userTimezones.size()) {
                         const int offsetTimeZone = currentDateTime.toTimeZone(m_userTimezones.at(iUserTimeZones).timeZone).offsetFromUtc();
                         if (offsetTimeZone < offsetUserTimeZone) {
                             break;
                         }
                         iUserTimeZones++;
                     }
                     m_userTimezones.insert(iUserTimeZones, userTimeZone);
                     multipleTimeZones();
                 }
                 watcher->deleteLater();
            });
        }
        connect(&m_timer, &QTimer::timeout, this, &DatetimeTipsWidget::multipleTimeZones);
        setText("");
    }
    else {
        connect(&m_timer, &QTimer::timeout, this, &DatetimeTipsWidget::oneTimeZone);
        oneTimeZone();
    }
    m_timer.start(1000);
}

void DatetimeTipsWidget::oneTimeZone()
{
    const QDateTime currentDateTime = QDateTime::currentDateTime();
    const QString tipLabel = currentDateTime.date().toString(Qt::SystemLocaleLongDate) + currentDateTime.toString(m_hourFormat);
    setText(tipLabel);
}

void DatetimeTipsWidget::multipleTimeZones()
{
    const QDateTime currentDateTime = QDateTime::currentDateTime();
    QStringList tips;
    for (int i = 0; i < m_userTimezones.size(); i++) {
        const UserTimezone userTimeZone = m_userTimezones.at(i);
        const QDateTime dateTime = currentDateTime.toTimeZone(userTimeZone.timeZone);
        QString tipLabel = dateTime.date().toString(Qt::SystemLocaleLongDate) + dateTime.toString(m_hourFormat) + userTimeZone.zoneName;
        tips.append(tipLabel);
    }
    setText(tips.join('\n'));
}
