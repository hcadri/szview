//
// Created by A C on 7/20/24.
//

#ifndef ABSTRACTVIEWER_H
#define ABSTRACTVIEWER_H

#include <QObject>
#include <QtCompilerDetection>

#if defined(QT_SHARED) || !defined(QT_STATIC)
#  if defined(BUILD_ABSTRACTVIEWER_LIB)
#    define ABSTRACTVIEWER_EXPORT Q_DECL_EXPORT
#  else
#    define ABSTRACTVIEWER_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define ABSTRACTVIEWER_EXPORT
#endif

QT_BEGIN_NAMESPACE
class QAction;
class QFile;
class QMainWindow;
class QMenu;
class QMenuBar;
class QPrinter;
class QToolBar;
class QTabWidget;
class QScrollArea;
class QStatusBar;
QT_END_NAMESPACE



class ABSTRACTVIEWER_EXPORT AbstractViewer : public QObject
{
    Q_OBJECT

protected:
    AbstractViewer();

public:
    virtual ~AbstractViewer();
    virtual void init(QFile *file, QWidget *widget, QMainWindow *mainWindow);
    void initViewer(QAction *back, QAction *forward, QAction *help, QTabWidget *tabs);
    virtual QString viewerName() const = 0;
    virtual bool restoreState(QByteArray &) = 0;
    virtual bool hasContent() const;
    virtual bool supportsOverview() const;
    virtual QStringList supportedMimeTypes() const = 0;
    virtual QStringList supportedExtensions() const { return {}; }
    virtual bool isDefaultViewer() const;
    virtual void cleanup();
    bool isEmpty() const;
    AbstractViewer *viewer();
    const AbstractViewer *viewer() const;

    QList<QAction *> actions() const;
    QWidget *widget() const;
    QList<QMenu *> menus() const;

signals:
    void uiInitialized();
    void showMessage(const QString &message, int timeout = 8000);
    void documentLoaded(const QString &fileName);

protected:

    struct UiAssets {
        QMainWindow *mainWindow = nullptr;
        QAction *back = nullptr;
        QAction *forward = nullptr;
        QAction *help = nullptr;
        QTabWidget *tabs = nullptr;
    } m_uiAssets;

    void statusMessage(const QString &message, const QString &type = QString(), int timeout = 8000);
    QToolBar *addToolBar(const QString &);
    QMenu *addMenu(const QString &);
    QMenu *fileMenu();
    QMainWindow *mainWindow() const;
    QStatusBar *statusBar() const;
    QMenuBar *menuBar() const;

    std::unique_ptr<QFile> m_file;
    QList<QAction *> m_actions;
    QWidget *m_widget = nullptr;
    QList<QMetaObject::Connection> m_connections;

private:
    QList<QMenu *> m_menus;
    QList<QToolBar *> m_toolBars;
};




#endif //ABSTRACTVIEWER_H
