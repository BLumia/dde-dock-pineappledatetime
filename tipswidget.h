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


#ifndef TIPSWIDGET_H
#define TIPSWIDGET_H

#include <QFrame>

class TipsWidget : public QFrame
{
    Q_OBJECT
public:
    explicit TipsWidget(QWidget *parent = nullptr);
    explicit TipsWidget(const bool deleteOnHide, QWidget *parent = nullptr);
    explicit TipsWidget(Qt::Alignment textAlignement, const bool deleteOnHide = false, QWidget *parent = nullptr);
    void setText(const QString &text);
protected:
    void paintEvent(QPaintEvent *event) override;
    void hideEvent(QHideEvent *event) override;
private:
    Qt::Alignment m_textAlignement;
    bool m_deleteOnHide;
    QString m_text;
};

#endif // TIPSWIDGET_H
