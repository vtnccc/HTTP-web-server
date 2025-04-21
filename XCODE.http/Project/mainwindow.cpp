#include "mainwindow.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QStyle>
#include <QToolBar>
#include <QListWidgetItem>

FileListItem::FileListItem(const QString &filePath, QListWidget *parent)
    : QWidget(parent), m_filePath(filePath)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(5, 2, 5, 2);
    layout->setSpacing(10);
    
    QLabel *iconLabel = new QLabel(this);
    iconLabel->setPixmap(style()->standardIcon(QStyle::SP_FileIcon).pixmap(16, 16));
    
    QLabel *pathLabel = new QLabel(filePath, this);
    pathLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    pathLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    
    QToolButton *removeBtn = new QToolButton(this);
    removeBtn->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    removeBtn->setToolTip("Remove file");
    removeBtn->setStyleSheet("QToolButton { border: none; padding: 2px; }");
    
    layout->addWidget(iconLabel);
    layout->addWidget(pathLabel, 1);
    layout->addWidget(removeBtn);
    
    connect(removeBtn, &QToolButton::clicked, this, &FileListItem::removeRequested);
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // Initialize filter menu and actions
    filterMenu = new QMenu(this);
    
    htmlAction = new QAction("HTML (.html, .htm)", this);
    htmlAction->setCheckable(true);
    htmlAction->setChecked(true);
    
    cssAction = new QAction("CSS (.css)", this);
    cssAction->setCheckable(true);
    cssAction->setChecked(true);
    
    jsAction = new QAction("JavaScript (.js)", this);
    jsAction->setCheckable(true);
    jsAction->setChecked(true);
    
    phpAction = new QAction("PHP (.php)", this);
    phpAction->setCheckable(true);
    
    imageAction = new QAction("Images (.png, .jpg, etc.)", this);
    imageAction->setCheckable(true);
    
    otherAction = new QAction("Other Files", this);
    otherAction->setCheckable(true);

    filterMenu->addAction(htmlAction);
    filterMenu->addAction(cssAction);
    filterMenu->addAction(jsAction);
    filterMenu->addAction(phpAction);
    filterMenu->addAction(imageAction);
    filterMenu->addAction(otherAction);

    // Filter button
    filterBtn = new QToolButton(this);
    filterBtn->setIcon(style()->standardIcon(QStyle::SP_FileDialogContentsView));
    filterBtn->setToolTip("File Filters");
    filterBtn->setPopupMode(QToolButton::InstantPopup);
    filterBtn->setMenu(filterMenu);

    // File input components
    filePathInput = new QLineEdit(this);
    browseBtn = new QPushButton("Browse", this);
    addFileBtn = new QPushButton("Add File", this);

    // File list
    fileList = new QListWidget(this);
    fileList->setSelectionMode(QAbstractItemView::SingleSelection);
    fileList->setStyleSheet(
        "QListWidget {"
        "    border: 1px solid #ccc;"
        "    border-radius: 3px;"
        "    background-color: grey;"
        "}"
        "QListWidget::item {"
        "    border-bottom: 1px solid #eee;"
        "    height: 30px;"
        "    background-color: #555555;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: #444555 ;"  // Light blue hover color
        "    border: 1px solid #cce0ff;"  // Optional border on hover
        "}"
        "QListWidget::item:selected {"
        "    background-color: #cce0ff;"   // Slightly darker blue when selected
        "    color: black;"
        "}"
    );

    // Server configuration
    protocolCombo = new QComboBox(this);
    protocolCombo->addItems({"HTTP", "HTTPS"});
    
    ipCombo = new QComboBox(this);
    ipCombo->addItems({"IPv4", "IPv6"});

    // Control buttons
    runBtn = new QPushButton(this);
    runBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    runBtn->setToolTip("Run Server");
    
    stopBtn = new QPushButton(this);
    stopBtn->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopBtn->setToolTip("Stop Server");
    
    refreshBtn = new QPushButton(this);
    refreshBtn->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    refreshBtn->setToolTip("Refresh");

    // Layout setup
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);

    // Filter toolbar
    QHBoxLayout *filterLayout = new QHBoxLayout();
    filterLayout->addWidget(new QLabel("File Types:"));
    filterLayout->addWidget(filterBtn);
    filterLayout->addStretch();
    mainLayout->addLayout(filterLayout);

    // File input area
    QHBoxLayout *fileInputLayout = new QHBoxLayout();
    fileInputLayout->addWidget(filePathInput, 1);
    fileInputLayout->addWidget(browseBtn);
    fileInputLayout->addWidget(addFileBtn);
    mainLayout->addLayout(fileInputLayout);

    // File list area
    QGroupBox *fileListGroup = new QGroupBox("Server Files", this);
    QVBoxLayout *fileListLayout = new QVBoxLayout();
    fileListLayout->addWidget(fileList);
    fileListGroup->setLayout(fileListLayout);
    mainLayout->addWidget(fileListGroup, 1);

    // Server configuration
    QGroupBox *serverGroup = new QGroupBox("Server Configuration", this);
    QVBoxLayout *serverLayout = new QVBoxLayout();
    
    QHBoxLayout *protocolLayout = new QHBoxLayout();
    protocolLayout->addWidget(new QLabel("Protocol:"));
    protocolLayout->addWidget(protocolCombo, 1);
    serverLayout->addLayout(protocolLayout);
    
    QHBoxLayout *ipLayout = new QHBoxLayout();
    ipLayout->addWidget(new QLabel("IP Type:"));
    ipLayout->addWidget(ipCombo, 1);
    serverLayout->addLayout(ipLayout);
    
    serverGroup->setLayout(serverLayout);
    mainLayout->addWidget(serverGroup);

    // Control buttons
    QHBoxLayout *controlLayout = new QHBoxLayout();
    controlLayout->addStretch();
    controlLayout->addWidget(runBtn);
    controlLayout->addWidget(stopBtn);
    controlLayout->addWidget(refreshBtn);
    mainLayout->addLayout(controlLayout);

    // Connect signals
    connect(browseBtn, &QPushButton::clicked, this, &MainWindow::browseFiles);
    connect(addFileBtn, &QPushButton::clicked, this, &MainWindow::addFileToServer);
    connect(filterBtn, &QToolButton::clicked, this, &MainWindow::showFilterMenu);
    connect(htmlAction, &QAction::toggled, this, &MainWindow::updateFileFilters);
    connect(cssAction, &QAction::toggled, this, &MainWindow::updateFileFilters);
    connect(jsAction, &QAction::toggled, this, &MainWindow::updateFileFilters);
    connect(phpAction, &QAction::toggled, this, &MainWindow::updateFileFilters);
    connect(imageAction, &QAction::toggled, this, &MainWindow::updateFileFilters);
    connect(otherAction, &QAction::toggled, this, &MainWindow::updateFileFilters);

    // Initialize filters
    updateFileFilters();
}

void MainWindow::showFilterMenu()
{
    filterMenu->exec(filterBtn->mapToGlobal(QPoint(0, filterBtn->height())));
}

void MainWindow::updateFileFilters()
{
    currentFilters.clear();
    supportedExtensions.clear();

    if (htmlAction->isChecked())
    {
        currentFilters += "HTML Files (*.html *.htm);;";
        supportedExtensions << "html" << "htm";
    }
    if (cssAction->isChecked())
    {
        currentFilters += "CSS Files (*.css);;";
        supportedExtensions << "css";
    }
    if (jsAction->isChecked())
    {
        currentFilters += "JavaScript Files (*.js);;";
        supportedExtensions << "js";
    }
    if (phpAction->isChecked())
    {
        currentFilters += "PHP Files (*.php);;";
        supportedExtensions << "php";
    }
    if (imageAction->isChecked())
    {
        currentFilters += "Image Files (*.png *.jpg *.jpeg *.gif *.svg *.webp);;";
        supportedExtensions << "png" << "jpg" << "jpeg" << "gif" << "svg" << "webp";
    }
    if (otherAction->isChecked())
    {
        currentFilters += "All Files (*.*)";
    }

    if (currentFilters.endsWith(";;"))
    {
        currentFilters.chop(2);
    }
}

void MainWindow::browseFiles()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Select File",
        "",
        currentFilters
    );

    if (!fileName.isEmpty())
    {
        filePathInput->setText(fileName);
    }
}

void MainWindow::addFileToServer()
{
    QString filePath = filePathInput->text();
    if (filePath.isEmpty())
    {
        QMessageBox::warning(this, "Error", "No file selected");
        return;
    }

    QFileInfo fileInfo(filePath);
    QString extension = fileInfo.suffix().toLower();

    if (!otherAction->isChecked() && !supportedExtensions.contains(extension))
    {
        QMessageBox::warning(this, "Error", "This file type is not enabled in filters");
        return;
    }

    // Check if file already exists in list
    for (int i = 0; i < fileList->count(); ++i)
    {
        QListWidgetItem *item = fileList->item(i);
        FileListItem *widget = qobject_cast<FileListItem*>(fileList->itemWidget(item));
        if (widget && widget->filePath() == filePath)
        {
            QMessageBox::warning(this, "Error", "This file is already in the list");
            return;
        }
    }

    // Create custom widget for the file entry
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(0, 30));
    FileListItem *fileWidget = new FileListItem(filePath, fileList);
    
    fileList->addItem(item);
    fileList->setItemWidget(item, fileWidget);
    
    connect(fileWidget, &FileListItem::removeRequested, this, [this, item]() {
        this->removeFile(item);
    });

    filePathInput->clear();
}

void MainWindow::removeFile(QListWidgetItem *item)
{
    if (item)
    {
        int row = fileList->row(item);
        fileList->takeItem(row);
        delete item;
    }
}
