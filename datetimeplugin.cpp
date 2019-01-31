/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 * 	           blumia <wzc782970009@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 * 	           blumia <wzc782970009@gmail.com>
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

#include "datetimeplugin.h"
#include "datetimetipswidget.h"

#include <DDBusSender>
#include <QLabel>
#include <QDebug>

#define PLUGIN_STATE_KEY "enable"

DatetimePlugin::DatetimePlugin(QObject *parent)
    : QObject(parent),

      m_dateTipsLabel(new QLabel),

      m_refershTimer(new QTimer(this)),
      m_settings("deepin", "dde-dock-pineappledatetime")
{
    m_dateTipsLabel->setObjectName("datetime");
    m_dateTipsLabel->setStyleSheet("color:white;"
                                   "padding:0px 3px;");

    m_refershTimer->setInterval(1000);
    m_refershTimer->start();

    m_centralWidget = new DatetimeWidget;

    connect(m_centralWidget, &DatetimeWidget::requestUpdateGeometry, [this] { m_proxyInter->itemUpdate(this, pluginName()); });

    connect(m_refershTimer, &QTimer::timeout, this, &DatetimePlugin::updateCurrentTimeString);
}

const QString DatetimePlugin::pluginName() const
{
    return "pinappledatetime";
}

const QString DatetimePlugin::pluginDisplayName() const
{
    return QString("Pineapple ") + tr("Datetime");
}

void DatetimePlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    if (!pluginIsDisable()) {
        m_proxyInter->itemAdded(this, pluginName());
    }
}

void DatetimePlugin::pluginStateSwitched()
{
    m_proxyInter->saveValue(this, PLUGIN_STATE_KEY, pluginIsDisable());

    if (!pluginIsDisable()) {
        m_proxyInter->itemAdded(this, pluginName());
    } else {
        m_proxyInter->itemRemoved(this, pluginName());
    }
}

bool DatetimePlugin::pluginIsDisable()
{
    return !(m_proxyInter->getValue(this, PLUGIN_STATE_KEY, true).toBool());
}

int DatetimePlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    const QString key = QString("pos_%1").arg(displayMode());
    return m_settings.value(key, 0).toInt();
}

void DatetimePlugin::setSortKey(const QString &itemKey, const int order)
{
    Q_UNUSED(itemKey);

    const QString key = QString("pos_%1").arg(displayMode());
    m_settings.setValue(key, order);
}

QWidget *DatetimePlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_centralWidget;
}

QWidget *DatetimePlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return new DatetimeTipsWidget(m_centralWidget->is24HourFormat());
}

const QString DatetimePlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return "dbus-send --print-reply --dest=com.deepin.Calendar /com/deepin/Calendar com.deepin.Calendar.RaiseWindow";
}

const QString DatetimePlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    QList<QVariant> items;
    items.reserve(1);

    QMap<QString, QVariant> settings;
    settings["itemId"] = "settings";
    if (m_centralWidget->is24HourFormat()) {
        settings["itemText"] = tr("12 Hour Time");
    } else {
        settings["itemText"] = tr("24 Hour Time");
    }
    settings["isActive"] = true;
    items.push_back(settings);

    QMap<QString, QVariant> open;
    open["itemId"] = "open";
    open["itemText"] = tr("Time Settings");
    open["isActive"] = true;
    items.push_back(open);

    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    return QJsonDocument::fromVariant(menu).toJson();
}

void DatetimePlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey)
    Q_UNUSED(checked)

    if (menuId == "open") {
        DDBusSender()
        .service("com.deepin.dde.ControlCenter")
        .interface("com.deepin.dde.ControlCenter")
        .path("/com/deepin/dde/ControlCenter")
        .method(QString("ShowModule"))
        .arg(QString("pineappledatetime"))
        .call();
    } else {
        m_centralWidget->toggleHourFormat();
    }
}

void DatetimePlugin::updateCurrentTimeString()
{
    const QDateTime currentDateTime = QDateTime::currentDateTime();

    if (m_centralWidget->is24HourFormat()) {
        m_dateTipsLabel->setText(currentDateTime.date().toString(Qt::SystemLocaleLongDate) + currentDateTime.toString(" HH:mm:ss"));
    } else {
        m_dateTipsLabel->setText(currentDateTime.date().toString(Qt::SystemLocaleLongDate) + currentDateTime.toString(" hh:mm:ss A"));
    }

    const QString currentString = currentDateTime.toString("mm");

    if (currentString == m_currentTimeString) {
        return;
    }

    m_currentTimeString = currentString;
    m_centralWidget->update();
}
