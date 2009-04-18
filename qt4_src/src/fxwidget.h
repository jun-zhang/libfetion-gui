#ifndef FXWIDGET_H
#define FXWIDGET_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QWidget>
#include <QGridLayout>
#include <QLayout>
#include <QLabel>
#include <QResizeEvent>

#include <QtGui>
#include <QDebug>
#include "qwidgetresizehandler_p.h"


namespace fxgui{
class FxWidgetTitleBar;
class FxWidget:public QWidget{
	Q_OBJECT
	Q_PROPERTY(QPixmap background WRITE setBackground)
	Q_PROPERTY(int scaleLeft WRITE setBgScaleLeft);
	Q_PROPERTY(int scaleRight WRITE setBgScaleRight);
	Q_PROPERTY(int scaleBottom WRITE setBgScaleBottom);
	Q_PROPERTY(int scaleTop WRITE setBgScaleTop);
	
	//Q_PROPERTY(QPixmap hiddenBar WRITE setHiddenBar)
public:
	FxWidget(QWidget *parent=0,Qt::WindowFlags flag=(Qt::Window | Qt::FramelessWindowHint) );
public:
signals:
	void triggleMaximizeAndNormal();
protected:
	void resizeEvent(QResizeEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	void moveEvent(QMoveEvent *event);
	void updateWindowPositionType();
private:
	QPushButton *btnMaximize;
	QGridLayout *_mainLayout;
	QLabel *sideBarRL;  // sideBar right 
	QLabel *sideBarTB;  // sideBar bottom
	int bgScaleLeft;
	int bgScaleRight;
	int bgScaleTop;
	int bgScaleBottom;
	QPixmap backgroundPixmap;
	//QPixmap hiddenBarPixmap;
	bool _autoHide;
	enum WINDOW_POS{
		WP_LEFT=1,WP_RIGHT=2,WP_TOP=4,WP_BOTTOM=8,WP_HIDDEN=16,WP_NORMAL=0
	};
	int positionState;
	QSize orientSize;
public:
	//void setHiddenBar(QPixmap pix); use css instead
	void setBackground(QPixmap pix);
	void setBgScaleLeft(int p){bgScaleLeft = p;}
	void setBgScaleRight(int p){bgScaleRight = p;}
	void setBgScaleBottom(int p){bgScaleBottom = p;}
	void setBgScaleTop(int p){bgScaleTop = p;}
	void setLayout(QLayout*);
	void setWindowTitle(const QString & title);
	bool isAutoHide()const{return _autoHide;}
public:
	FxWidgetTitleBar *titleBar;
	QWidget *contentWidget;
public slots:
	void setAutoHide(bool autoHide=true){
		_autoHide = autoHide;
		if(_autoHide){
			setWindowFlags( windowFlags() | Qt::WindowStaysOnTopHint);
			if( isVisible() ){
				show();
			}
			updateWindowPositionType();
		}
	}
	void turnBackNormal();
	void hideToTopBottom();
	void hideToLeftRight();
	void onDoubleClicked(bool checked);
};//class FxWidget

}// namespace fxgui
#endif
