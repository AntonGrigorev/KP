#include "anotherwin.hpp"

AnotherWin::AnotherWin(QWidget* parent) {
    //Выбор типа графа
    setWindowTitle("Graph type");
    label1 = new QLabel("Choose a type of graph to be build", this);
    linearButton = new QPushButton("Linear graph", this);
    logButton = new QPushButton("Logarithmic graph", this);
    linlogButton = new QPushButton("Lin-log graph", this);
    loglinButton = new QPushButton("Log-lin graph", this);
    QHBoxLayout* layout1 = new QHBoxLayout(this);
    layout1->addWidget(label1);
    layout1->addWidget(linearButton);
    layout1->addWidget(logButton);
    layout1->addWidget(linlogButton);
    layout1->addWidget(loglinButton);
    connect(linearButton, SIGNAL(clicked(bool)),
        this, SLOT(clicked_linear()));
    connect(logButton, SIGNAL(clicked(bool)),
        this, SLOT(clicked_log()));
    connect(linlogButton, SIGNAL(clicked(bool)),
        this, SLOT(clicked_linlog()));
    connect(loglinButton, SIGNAL(clicked(bool)),
        this, SLOT(clicked_loglin()));
}

void AnotherWin::clicked_linear() {
    drawer object;
    object.set_linear_x();
    object.set_linear_y();
    object.cicle(data_.first, data_.second);
}

void AnotherWin::clicked_log() {
    for (int i = 0; i < data_.first.size(); i++) {
        if (data_.first[i] <= 0 || data_.second[i] <= 0) {
            QMessageBox::information(this, tr("Error"),
                tr("Logarithmic scale grapth can`t be built using negative numbers"));
            return;
        }
    }
    drawer object;
    object.set_log_x();
    object.set_log_y();
    object.cicle(data_.first, data_.second);
}

void AnotherWin::clicked_linlog() {
    for (int i = 0; i < data_.first.size(); i++) {
        if (data_.second[i] <= 0) {
            QMessageBox::information(this, tr("Error"),
                tr("Logarithmic scale grapth can`t be built using negative numbers"));
            return;
        }
    }
    drawer object;
    object.set_linear_x();
    object.set_log_y();
    object.cicle(data_.first, data_.second);
}

void AnotherWin::clicked_loglin() {
    for (int i = 0; i < data_.first.size(); i++) {
        if (data_.first[i] <= 0) {
            QMessageBox::information(this, tr("Error"),
                tr("Logarithmic scale grapth can`t be built using negative numbers"));
            return;
        }
    }
    drawer object;
    object.set_log_x();
    object.set_linear_y();
    object.cicle(data_.first, data_.second);
}

void AnotherWin::set_data(const std::pair<std::vector<double>, std::vector<double>>& data1) {
    data_ = data1;
}


#include "moc_anotherwin.cpp"
