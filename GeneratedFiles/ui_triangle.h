/********************************************************************************
** Form generated from reading UI file 'triangle.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRIANGLE_H
#define UI_TRIANGLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include "qopenwidget.h"

QT_BEGIN_NAMESPACE

class Ui_triangleClass
{
public:
    QOPenWidget *openGLWidget;

    void setupUi(QDialog *triangleClass)
    {
        if (triangleClass->objectName().isEmpty())
            triangleClass->setObjectName(QStringLiteral("triangleClass"));
        triangleClass->resize(600, 400);
        openGLWidget = new QOPenWidget(triangleClass);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(70, 40, 411, 211));

        retranslateUi(triangleClass);

        QMetaObject::connectSlotsByName(triangleClass);
    } // setupUi

    void retranslateUi(QDialog *triangleClass)
    {
        triangleClass->setWindowTitle(QApplication::translate("triangleClass", "triangle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class triangleClass: public Ui_triangleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRIANGLE_H
