#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextDocument>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QFont>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QList>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void loadClicked();
    void processClicked();
private:
    void boldWord(int startOfWord, int endOfWord);
    //Elements
    QTextDocument *document = new QTextDocument;
    QTextEdit *editor = new QTextEdit(this);
    QList<QRegularExpression> regularExpressionList; //A list to help loop through possible matches
    QRegularExpression emailRegex;
    QRegularExpression numberRegex0;
    QRegularExpression numberRegex1;
    QRegularExpression numberRegex2;
    QRegularExpression numberRegex3;
    QRegularExpression numberRegex4;
    //Buttons
    QPushButton *loadButton = new QPushButton("Load");
    QPushButton *processButton = new QPushButton("Process");
    //Layout
    QVBoxLayout *verticleLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QWidget *theCentralWidget = new QWidget;
};

#endif // MAINWINDOW_H
