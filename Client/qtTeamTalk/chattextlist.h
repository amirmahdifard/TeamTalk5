/*
 * Copyright (C) 2023, Bjørn D. Rasmussen, BearWare.dk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CHATTEXTLIST_H
#define CHATTEXTLIST_H

#include "common.h"
#include "chattextedit.h"

#include <QListWidget>
#include <QShortcut>

class ChatTextList : public QListWidget, public ChatTextHistory
{
    Q_OBJECT

public:
    ChatTextList(QWidget * parent = 0);

    void updateServer(const ServerProperties& srvprop) override;
    void joinedChannel(int channelid) override;

    QString addTextMessage(const MyTextMessage& msg) override;
    void addLogMessage(const QString& msg) override;
    bool hasFocus() const override { return QListWidget::hasFocus(); }
    void setFocus() override { QListWidget::setFocus(); }

    void updateTranslation() override;

    void clearHistory();
    void copyAllHistory();

private:
    static QString getTimeStamp(const QDateTime& tm);
    QString getTextMessagePrefix(const TextMessage& msg, const User& user);
    QStringList allUrls(const QString &text) const;
    QString currentUrl(const QListWidgetItem* item) const;
    void limitText();
    QShortcut *m_copy     = nullptr;
    QShortcut *m_copyContent     = nullptr;
    QShortcut *m_details  = nullptr;
    QShortcut *m_copyAll  = nullptr;    
    QShortcut *m_clear    = nullptr;
    enum MenuAction
    {
        COPY,
        COPYCONTENT,
        VIEWDETAILS,
        COPYALL,
        CLEAR
    };
    void menuAction(MenuAction ma);

protected:
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent* e) override;
    void mouseDoubleClickEvent(QMouseEvent* e) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
};


#include <QDialog>

class MessageDetailsDlg : public QDialog
{
    Q_OBJECT
public:
    explicit MessageDetailsDlg(const QString& datetime, const QString& sender, const QString& content, QWidget* parent = nullptr);
};
#endif
