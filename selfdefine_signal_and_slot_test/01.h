#pragma once
#include <QObject>

class Newspaper : public QObject {
	Q_OBJECT
public:
	Newspaper(const QString & name): m_name(name)
	{
	}
	void send() {
		emit newPaper(m_name);//哪份报纸发出的信号？
	}
signals:
	void newPaper(const QString & name);//形参随便写一个变量
private:
	QString m_name;
};