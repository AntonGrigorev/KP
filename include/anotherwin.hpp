#ifndef anotherwin_hpp
#define anotherwin_hpp
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QObject>
#include <string>
#include <iostream>
#include <drawer.hpp>
#include <QMessageBox>
#include <QApplication>

class AnotherWin : public QDialog {
	Q_OBJECT
public:
	AnotherWin(QWidget* parent = 0);
public slots:
	void clicked_linear();
	void clicked_log();
	void clicked_linlog();
	void clicked_loglin();
	void set_data(const std::pair<std::vector<double>, std::vector<double>>& data1);
private:
	QLabel* label1;
	QPushButton* linearButton;
	QPushButton* logButton;
	QPushButton* linlogButton;
	QPushButton* loglinButton;
	std::pair<std::vector<double>, std::vector<double>> data_;
};

#endif
