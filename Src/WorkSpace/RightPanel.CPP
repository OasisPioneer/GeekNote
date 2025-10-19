#include "../../Include/WorkSpace/RightPanel.HPP"
#include "../../Include/Utility/LoadingStyles.HPP"

#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QLineEdit>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QToolButton>


RightPanel::RightPanel(QSettings* Setting, QWidget* Parent)
    : Setting_(Setting), QWidget(Parent) {
    setObjectName("RightPanel");
    // setAutoFillBackground(true);
    setAttribute(Qt::WA_StyledBackground);

    QVBoxLayout* MainLayout = new QVBoxLayout(this);

    QHBoxLayout* TopLayout = new QHBoxLayout;
    QLabel* SearchIcon = new QLabel;
    SearchIcon->setPixmap(QPixmap(":/Image/search.svg").scaled(20, 20));
    SearchBox = new QLineEdit;
    SearchBox->setObjectName("SearchBox");
    SearchBox->setPlaceholderText(tr("SearchProject"));
    QPushButton* NewButton = new QPushButton(tr("New"));
    QPushButton* OpenButton = new QPushButton(tr("Open"));

    TopLayout->addWidget(SearchIcon);
    TopLayout->addWidget(SearchBox, 1);
    TopLayout->addWidget(NewButton);
    TopLayout->addWidget(OpenButton);

    // 滚动项目区
    QScrollArea* ScrollArea = new QScrollArea;
    ScrollArea->setObjectName("ScrollArea");
    QWidget* ScrollWidget = new QWidget;
    ScrollLayout = new QVBoxLayout(ScrollWidget);
    ScrollWidget->setLayout(ScrollLayout);
    ScrollArea->setWidget(ScrollWidget);
    ScrollArea->setWidgetResizable(true);

    MainLayout->addLayout(TopLayout);
    MainLayout->addWidget(ScrollArea);

    LoadProject();

    LoadingStyles(this, ":/QtStyleSheets/WorkSpaceRightPanel.qss");
}

void RightPanel::LoadProject() {
    QString JsonPath = Setting_->value(QCoreApplication::applicationName() + "/ProjectsFile", "projects.json").toString();
    QFile File(JsonPath);
    if (!File.open(QIODevice::ReadOnly)) return;

    QJsonDocument Doc = QJsonDocument::fromJson(File.readAll());

    const QJsonArray ItemArray = Doc.array();
    for (const QJsonValue& Val : ItemArray) {
        QJsonObject OBJ = Val.toObject();
        ScrollLayout->addWidget(CreateProjectCard(
            OBJ["Icon"].toString(),
            OBJ["Name"].toString(),
            OBJ["Path"].toString()
            ));
    }
    ScrollLayout->addStretch();
}

QWidget* RightPanel::CreateProjectCard(const QString& Icon, const QString& Name, const QString& Path) {
    QWidget* Card = new QWidget;
    QHBoxLayout* Layout = new QHBoxLayout(Card);

    QLabel* IconLabel = new QLabel;
    IconLabel->setPixmap(QPixmap(Icon).scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QVBoxLayout* InfoLayout = new QVBoxLayout;
    QLabel* NameLabel = new QLabel(Name);
    QLabel* PathLabel = new QLabel(Path);
    PathLabel->setStyleSheet("color: gray; font-size: 12px;");
    InfoLayout->addWidget(NameLabel);
    InfoLayout->addWidget(PathLabel);

    QToolButton* SettingsButton = new QToolButton;
    SettingsButton->setIcon(QIcon(":/Image/settings.svg"));
    SettingsButton->setToolTip(tr("ProjectSettings"));

    Layout->addWidget(IconLabel);
    Layout->addLayout(InfoLayout, 1);
    Layout->addWidget(SettingsButton);

    Card->setStyleSheet("QWidget { border: 1px solid #ccc; border-radius: 5px; padding: 8px; }");
    return Card;
}
