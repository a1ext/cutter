#include "CutterDockWidget.h"
#include "MainWindow.h"


CutterDockWidget::CutterDockWidget(MainWindow *main, QAction *action) :
    QDockWidget(main),
    action(action)
{
    if (action) {
        main->addToDockWidgetList(this);
        main->addDockWidgetAction(this, action);
        connect(action, &QAction::triggered, this, &CutterDockWidget::toggleDockWidget);
    }
}


void CutterDockWidget::toggleDockWidget(bool show)
{
    if (!show) {
        this->close();
    } else {
        this->show();
        this->raise();
    }
}

void CutterDockWidget::setDockUniqueObjectName()
{
    static const QString kNamePattern = QStringLiteral("%1#%2");
    const QString &name = metaObject()->className();
    quint64 num = 0;
    QString newName;
    while (parent()->findChild<CutterDockWidget*>(newName = kNamePattern.arg(name).arg(num))) {
        ++num;
    }

    setObjectName(newName);
}

void CutterDockWidget::closeEvent(QCloseEvent *event)
{
    if (action) {
        this->action->setChecked(false);
    }
    QDockWidget::closeEvent(event);
}

CutterDockWidget::~CutterDockWidget() {}
