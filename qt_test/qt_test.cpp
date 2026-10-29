#include "qt_test.h"
#include <QPushButton>
#include <QDebug>

qt_test::qt_test(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	m_Btn = new QPushButton("123123",this);
	m_Btn->resize(100, 30);

    connect(m_Btn, &QPushButton::clicked, this,
        [this](bool) {
            qDebug() << "clicked me";
        });
}

qt_test::~qt_test()
{}

