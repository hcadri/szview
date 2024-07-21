// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "abstractviewer.h"

#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QScrollArea>
#include <QStatusBar>
#include <QTabWidget>
#include <QToolBar>

#include <QAction>

#include <QFile>
#include <QSettings>

#ifdef QT_DOCUMENTVIEWER_PRINTSUPPORT
#include <QPrinter>
#include <QPrintDialog>
#endif // QT_DOCUMENTVIEWER_PRINTSUPPORT

using namespace Qt::StringLiterals;

AbstractViewer::AbstractViewer() : m_file(nullptr), m_widget(nullptr)
{
}

void AbstractViewer::init(QFile *file, QWidget *widget, QMainWindow *mainWindow)
{
    Q_ASSERT(widget);
    Q_ASSERT(mainWindow);
    Q_ASSERT(file);
    m_file.reset(file);
    m_widget = widget;
    m_uiAssets.mainWindow = mainWindow;
}

AbstractViewer::~AbstractViewer()
{
    AbstractViewer::cleanup();
}

bool AbstractViewer::isEmpty() const
{
    return !hasContent();
}

bool AbstractViewer::hasContent() const
{
    return false;
}

QList<QAction *> AbstractViewer::actions() const
{
    return m_actions;
}

QWidget *AbstractViewer::widget() const
{
    return m_widget;
}

QList<QMenu *> AbstractViewer::menus() const
{
    return m_menus;
}

QMainWindow *AbstractViewer::mainWindow() const
{
    return m_uiAssets.mainWindow;
}

QStatusBar *AbstractViewer::statusBar() const
{
    return mainWindow()->statusBar();
}
bool AbstractViewer::supportsOverview() const
{
    return false;
}

QMenuBar *AbstractViewer::menuBar() const
{
    return mainWindow()->menuBar();
}

bool AbstractViewer::isDefaultViewer() const
{
    return false;
}

AbstractViewer *AbstractViewer::viewer()
{
    return this;
}

const AbstractViewer *AbstractViewer::viewer() const
{
    return this;
}

void AbstractViewer::statusMessage(const QString &message, const QString &type, int timeout)
{
    const QString msg = viewerName()
                        + (type.isEmpty() ? ": "_L1 : "/"_L1 + type + ": "_L1) + message;
    emit showMessage(msg, timeout);
}

QToolBar *AbstractViewer::addToolBar(const QString &title)
{
    auto *bar = mainWindow()->addToolBar(title);
    QString name = title;
    name.remove(u' ');
    bar->setObjectName(name);
    m_toolBars.append(bar);
    return bar;
}

QMenu *AbstractViewer::addMenu(const QString &title)
{
    QMenu *menu = new QMenu(title, menuBar());
    menu->setObjectName(title);
    menuBar()->insertMenu(m_uiAssets.help, menu);
    m_menus.append(menu);
    return menu;
}

void AbstractViewer::cleanup()
{
    // delete all objects created by the viewer which need to be displayed
    // and therefore parented on MainWindow
    if (m_file)
        m_file.reset();

    qDeleteAll(m_menus);
    m_menus.clear();
    qDeleteAll(m_toolBars);
    m_toolBars.clear();

    for (const auto &connection : m_connections)
        QObject::disconnect(connection);

    m_connections.clear();
}

QMenu *AbstractViewer::fileMenu()
{
    static constexpr QLatin1StringView name = QLatin1StringView("qtFileMenu");
    static QMenu *fileMenu = nullptr;
    if (fileMenu)
        return fileMenu;

    const QList<QMenu *> menus = mainWindow()->findChildren<QMenu *>();
    for (auto *menu : menus) {
        if (menu->objectName() == name) {
            fileMenu = menu;
            return fileMenu;
        }
    }
    fileMenu = addMenu(tr("&File"));
    fileMenu->setObjectName(name);
    return fileMenu;
}


void AbstractViewer::initViewer(QAction *back, QAction *forward, QAction *help, QTabWidget *tabs)
{
    // Viewers need back & forward buttons and a tab widget.
    Q_ASSERT(back);
    Q_ASSERT(forward);
    Q_ASSERT(tabs);
    Q_ASSERT(help);

    m_uiAssets.back = back;
    m_uiAssets.forward = forward;
    m_uiAssets.help = help;
    m_uiAssets.tabs = tabs;

    // Tabs can be populated individually by the viewer, if it supports overview
    tabs->clear();
    tabs->setVisible(supportsOverview());

    emit uiInitialized();
}
