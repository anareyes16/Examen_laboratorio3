#include "ClientChatWidget.h"
#include "ui_ClientChatWidget.h"

ClientChatWidget::ClientChatWidget(QTcpSocket *client,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientChatWidget),
    _client(client)
{
    ui->setupUi(this);
    connect(_client, &QTcpSocket::readyRead, this, &ClientChatWidget::dataReceived);
 connect(_client, &QTcpSocket::disconnected, this, &ClientChatWidget::clientDisconnected);

// dir.mkdir(_client->name());
// dir.setPath("./" + _client->name());
}

ClientChatWidget::~ClientChatWidget()
{
    delete ui;
}

void ClientChatWidget::dataReceived()
{
    auto data = _client->readAll();
    ui->listMensajes->addItem(data);
}

void ClientChatWidget::on_btnEnviar_clicked()
{
    _client->write(ui->lnMessage->text().trimmed().toUtf8());
    ui->lnMessage->setText("");

}

void ClientChatWidget::clientDisconnected()
{
    ui->wdgSend->setEnabled(false);
}

