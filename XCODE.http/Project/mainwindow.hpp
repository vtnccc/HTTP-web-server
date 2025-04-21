#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QListWidget>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>

class FileListItem : public QWidget {
    Q_OBJECT
public:
    explicit FileListItem(const QString &filePath, QListWidget *parent = nullptr);
    QString filePath() const { return m_filePath; }

signals:
    void removeRequested();

private:
    QString m_filePath;
};

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void browseFiles();
    void addFileToServer();
    void updateFileFilters();
    void showFilterMenu();
    void removeFile(QListWidgetItem *item);

private:
    // Filter components
    QToolButton *filterBtn;
    QMenu *filterMenu;
    QAction *htmlAction;
    QAction *cssAction;
    QAction *jsAction;
    QAction *phpAction;
    QAction *imageAction;
    QAction *otherAction;

    // File components
    QLineEdit *filePathInput;
    QPushButton *browseBtn;
    QPushButton *addFileBtn;
    QListWidget *fileList;

    // Server components
    QComboBox *protocolCombo;
    QComboBox *ipCombo;
    QPushButton *runBtn;
    QPushButton *stopBtn;
    QPushButton *refreshBtn;

    // State
    QString currentFilters;
    QStringList supportedExtensions;
    
public:
};

#endif // MAINWINDOW_HPP
