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


#include "tipswidget.h"

#include <QPainter>

TipsWidget::TipsWidget(QWidget *parent) : TipsWidget(Qt::AlignCenter, false, parent)
{
}

TipsWidget::TipsWidget(const bool deleteOnHide, QWidget *parent) : TipsWidget(Qt::AlignCenter, deleteOnHide, parent)
{
}

TipsWidget::TipsWidget(Qt::Alignment textAlignement, const bool deleteOnHide, QWidget *parent) : QFrame(parent),
    m_textAlignement(textAlignement), m_deleteOnHide(deleteOnHide)
{
}

void TipsWidget::setText(const QString &text)
{
    m_text = text;

    setFixedSize(fontMetrics().size(Qt::TextExpandTabs, text));

    update();
}

void TipsWidget::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);

    QPen pen(Qt::white);
    painter.setPen(pen);

    QTextOption option;
    option.setAlignment(m_textAlignement);
    painter.drawText(rect(), m_text, option);
}

void TipsWidget::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event)
    if (m_deleteOnHide) {
        deleteLater();
    }
}
