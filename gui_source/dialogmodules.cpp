// copyright (c) 2019 hors<horsicq@gmail.com>
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
#include "dialogmodules.h"
#include "ui_dialogmodules.h"

DialogModules::DialogModules(QWidget *parent, QList<QObject *> *pListPlugins) :
    QDialog(parent),
    ui(new Ui::DialogModules)
{
    ui->setupUi(this);

//    echoInterface = qobject_cast<EchoInterface *>(plugin);
//                if (echoInterface)

    this->pListPlugins=pListPlugins;

    int nCount=pListPlugins->count();

    ui->tableWidgetModules->setRowCount(nCount);
    ui->tableWidgetModules->setColumnCount(1);

    QStringList listHeaderLabels;
    listHeaderLabels.append(tr("Name"));
    ui->tableWidgetModules->setHorizontalHeaderLabels(listHeaderLabels);

    for(int i=0;i<nCount;i++)
    {
        XvdgPluginInterface *pPluginInterface=qobject_cast<XvdgPluginInterface *>(pListPlugins->at(i));
        if(pPluginInterface)
        {
            QString sPluginName=pPluginInterface->getInfo().sName;
            QTableWidgetItem *pItem=new QTableWidgetItem(sPluginName);

            ui->tableWidgetModules->setItem(i,0,pItem);
        }
    }
}

DialogModules::~DialogModules()
{
    delete ui;
}

void DialogModules::on_pushButtonOK_clicked()
{
    this->close();
}