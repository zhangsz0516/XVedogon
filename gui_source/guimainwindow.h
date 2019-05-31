// Copyright (c) 2019 hors<horsicq@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#ifndef GUIMAINWINDOW_H
#define GUIMAINWINDOW_H

#include "../global.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QMimeData>
#include "dialogstaticscan.h"
#include "dialogoptions.h"
#include "dialogabout.h"
#include "dialogmodules.h"
#include "dialogviewer.h"
#include "plugin_interface.h"
#include "xvdg_utils.h"

namespace Ui {
class GuiMainWindow;
}

class GuiMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuiMainWindow(QWidget *parent =nullptr);
    ~GuiMainWindow();

private:
    struct SRECORD
    {
        SpecAbstract::SCAN_STRUCT scanStruct;
        QModelIndex modelIndex1;
        QModelIndex modelIndex2;
    };

    enum BUTTON_INFO_TYPE
    {
        BUTTON_INFO_TYPE_UNKNOWN=1,
        BUTTON_INFO_TYPE_VIEWER,
        BUTTON_INFO_TYPE_RTUNPACK // TODO Static
    };

    struct BUTTON_INFO
    {
        // TODO RunTime, directory
        XvdgPluginInterface *pPlugin;
        BUTTON_INFO_TYPE biType;
        qint64 nOffset;
        qint64 nSize;
    };

private slots:
    void on_pushButtonExit_clicked();
    void on_pushButtonOpenFile_clicked();
    void _scan(QString sFileName);
    void on_pushButtonScan_clicked();
    void adjust();

    void on_pushButtonOptions_clicked();
    void loadPlugins();

    void on_pushButtonAbout_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonSave_clicked();

    void on_pushButtonModules_clicked();

    void handleItem(QList<SRECORD> *pListButtons, StaticScanItem *pItem, StaticScanItemModel *pModel, QModelIndex modelIndexParent);
    void pushButtonSlot();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    Ui::GuiMainWindow *ui;
    XVDG::OPTIONS xvdgOptions;
    QList<QObject *> listPlugins;
    QMap<QString,BUTTON_INFO> mapButtonInfos;
};

#endif // GUIMAINWINDOW_H
