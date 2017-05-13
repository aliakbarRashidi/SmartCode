#include "SSmartCode.h"
#include "ui_SSmartCode.h"

void SSmartCode::setupCodeEditor()
{
    codeEditor = new SCodeEditor();
    codeEditor->setObjectName("pteCodeEditor");
    codeEditor->setTabStopWidth ( 33 );
    codeEditor->setFont( QFont("Consolas", 11) );
    codeEditor->setStyleSheet("background: rgb(80,80,80); "
                              "color: rgb(255, 255, 255); "
                              "border: 0px solid black;");
    highlighter = new SHighlighter(codeEditor->document());
    highlighter->updateHighlightRules(":/highlighter/SHighlighter/lisp.hp");

    connect(codeEditor,
            SIGNAL(cursorPositionChanged()),
            this,
            SLOT(codeEditorPosChanged()));

    ui->codeEditorLayout->addWidget(codeEditor);
}

void SSmartCode::setupTreeView()
{
    ui->tvProjectFiles->clear();
    ui->tvProjectFiles->header()->hide();
}

void SSmartCode::setupRightBar()
{
    ui->wRightSide->hide();
}

void SSmartCode::setupBottomBar()
{
    ui->wBotomSide->hide();
}

void SSmartCode::setupLeftBar()
{
    ui->wLeftSide->hide();
}

void SSmartCode::updateTreeView()
{
    ui->tvProjectFiles->clear();

    QDir dir(currentPath);

    QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->tvProjectFiles);
    rootItem->setIcon(0, this->style()->standardIcon(QStyle::SP_DirIcon) );
    rootItem->setText(0, QFileInfo(currentPath).fileName() );
    ui->tvProjectFiles->addTopLevelItem(rootItem);
    printDir(dir, rootItem);
}

void SSmartCode::printDir(const QDir &dir, QTreeWidgetItem *item)
{
    QFileInfoList dirContent = dir.entryInfoList(QDir::Files |
                                                 QDir::Dirs |
                                                 QDir::NoDotAndDotDot);

    for(int i = 0; i < dirContent.size(); i++)
    {
        QTreeWidgetItem *subItem = new QTreeWidgetItem(item);

        if( dirContent.at(i).isDir() )
        {
            QDir subDir(dirContent.at(i).absolutePath() +
                        "/" + dirContent.at(i).fileName());
            subItem->setIcon(0, this->style()->standardIcon(QStyle::SP_DirIcon));
            subItem->setText(0, dirContent.at(i).fileName() );
            printDir(subDir, subItem);
        }
        else
        {
            subItem->setIcon(0, this->style()->standardIcon(QStyle::SP_FileIcon));
            subItem->setText(0, dirContent.at(i).fileName() );
        }
    }
}

QString SSmartCode::dreelUp(QTreeWidgetItem *item)
{
    QString path = "";
    QTreeWidgetItem * parent = item;
    int i = 0;
    while(parent->parent())
    {
        if( i == 0 )
            path = parent->text(0);
        else
            path = parent->text(0) + "/" + path;

        parent = parent->parent();
        i++;
    }


    return path;
}
