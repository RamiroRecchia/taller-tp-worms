#include "sala_espera.h"
#include "ui/ui_sala_espera.h"

Sala_Espera::Sala_Espera(QWidget *parent, QMainWindow* mainWindow, Login_Window* ui1) :
    QWidget(parent),
    ui(new Ui::Sala_Espera) {
    ui->setupUi(this);
    this->mainWindow = mainWindow;
    this->ui1 = ui1;
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onComenzarButtonClicked()));
}

Sala_Espera::~Sala_Espera() {
    delete ui;
}

void Sala_Espera::onComenzarButtonClicked() {

    ClienteProtocolo protocol(*this->ui1->skt);
     if (protocol.recibir_comienzo_de_partida() == true) {
        return;
     }
    this->mainWindow->close();
}
