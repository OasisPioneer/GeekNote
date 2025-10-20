#include "../../Include/WorkSpace/LeftPanel.HPP"
#include "../../Include/Utility/LoadingStyles.HPP"

#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QPixmap>
#include <QMenu>
#include <QAction>

LeftPanel::LeftPanel(QSettings* Setting, QWidget* Parent) : Setting_(Setting), QWidget(Parent){
    setObjectName("LeftPanel");
    // setAutoFillBackground(true);
    setAttribute(Qt::WA_StyledBackground);
    setFixedWidth(200);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QVBoxLayout* MainLayout = new QVBoxLayout(this);

    QLabel* LOGO = new QLabel;
    LOGO->setPixmap(QPixmap(":/Image/GeekNote.png").scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    LOGO->setAlignment(Qt::AlignVCenter);

    NameLabel = new QLabel(QCoreApplication::applicationName());
    VersionLabel = new QLabel("V " + QCoreApplication::applicationVersion());
    NameLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
    VersionLabel->setStyleSheet("font-weight: bold; font-size: 12px; font-style: italic;");

    QVBoxLayout* NameVersionLayout = new QVBoxLayout;
    NameVersionLayout->addWidget(NameLabel);
    NameVersionLayout->addWidget(VersionLabel);
    NameVersionLayout->setSpacing(2);
    NameVersionLayout->setAlignment(Qt::AlignVCenter);

    QHBoxLayout* LogoLayout = new QHBoxLayout;
    LogoLayout->addWidget(LOGO);
    LogoLayout->addLayout(NameVersionLayout);
    LogoLayout->setSpacing(5);
    LogoLayout->setContentsMargins(0, 0, 0, 0);
    LogoLayout->setAlignment(Qt::AlignLeft);

    NoteRepo = new QPushButton(tr("NoteRepo"));
    NoteRepo->setObjectName("NoteRepo");
    NoteRepo->setCheckable(true);
    // NOTE: 这里后续可能会增加其它按钮

    ButtonGroup = new QButtonGroup(this);
    ButtonGroup->addButton(NoteRepo, 0);
    // ButtonGroup->addButton(SettingsButton, 1);
    // ButtonGroup->addButton(AboutButton, 2);
    ButtonGroup->setExclusive(true);

    // connect(NoteRepo, &QPushButton::clicked, [this]() { emit SwitchPages(0); });
    // connect(ButtonGroup, &QButtonGroup::idClicked, this, &LeftPanel::SwitchPages);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    connect(ButtonGroup, &QButtonGroup::idClicked, this, &LeftPanel::SwitchPages);
#else
    connect(ButtonGroup, static_cast<void(QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked),
            this, [this](QAbstractButton* btn){
                if (!btn) return;
                emit SwitchPages(ButtonGroup->id(btn));
            });
#endif


    OptionsMenuButton = new QPushButton;
    OptionsMenuButton->setObjectName("OptionsMenuButton");
    OptionsMenuButton->setIcon(QIcon(":/Image/settings.svg"));
    OptionsMenuButton->setIconSize(QSize(18, 18));
    OptionsMenuButton->setFixedSize(24, 24);
    // OptionsMenuButton->setFlat(true);
    OptionsMenuButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    OptionsMenuButton->setFocusPolicy(Qt::NoFocus);
    OptionsMenuButton->setToolTip(tr("Options Menu"));
    OptionsMenuButton->setText("");
    connect(OptionsMenuButton, &QPushButton::clicked, this, &LeftPanel::ShowSettingsMenu);

    MainLayout->addLayout(LogoLayout);
    MainLayout->addStretch();
    MainLayout->addWidget(NoteRepo);
    MainLayout->addStretch();
    MainLayout->addStretch();
    MainLayout->addStretch();
    MainLayout->addStretch();
    MainLayout->addStretch();
    MainLayout->addWidget(OptionsMenuButton, 0, Qt::AlignLeft);

    NoteRepo->setChecked(true);

    LoadingStyles(this, ":/QtStyleSheets/WorkSpaceLeftPanel.qss");
}

void LeftPanel::SettingActivitiePage(int Index) {
    if (QAbstractButton* Btn = ButtonGroup->button(Index))
        Btn->setChecked(true);
}

void LeftPanel::ShowSettingsMenu(){
    QMenu Menu;
    QAction* Setting = Menu.addAction(tr("Setting"));
    // QAction* Theme = Menu.addAction(tr("Theme"));
    QAction* Exit = Menu.addAction(tr("Exit"));

    QAction* Choose = Menu.exec(OptionsMenuButton->mapToGlobal(QPoint(0, OptionsMenuButton->height())));
    if (Choose == Setting) emit SettingRequest();
    else if (Choose == Exit) qApp->quit();
}
