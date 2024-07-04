#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Search");
    document = editor->document();

    //Layout
    theCentralWidget->setLayout(verticleLayout);
    setCentralWidget(theCentralWidget);
    verticleLayout->addLayout(buttonLayout);
        buttonLayout->addWidget(loadButton);
        buttonLayout->addWidget(processButton);
    verticleLayout->addWidget(editor);

    //Regular expression
    editor->setAcceptRichText(true);
    emailRegex.setPattern("@");
        regularExpressionList.append(emailRegex);
    numberRegex0.setPattern("\\b\\d{3}-\\d{3}-\\d{4}\\b");
        regularExpressionList.append(numberRegex0);
    numberRegex1.setPattern("\\b\\d{3}-\\d{7}\\b");
        regularExpressionList.append(numberRegex1);
    numberRegex2.setPattern("\\b\\d{10}\\b");
        regularExpressionList.append(numberRegex2);
    numberRegex3.setPattern("\\(\\d{3}\\)\\d{3}-\\d{4}");
        regularExpressionList.append(numberRegex3);
    numberRegex4.setPattern("\\(\\d{3}\\)\\d{7}");
        regularExpressionList.append(numberRegex4);

    //Signals &slots
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadClicked);
    connect(processButton, &QPushButton::clicked, this, &MainWindow::processClicked);
}

MainWindow::~MainWindow()
{

}

void MainWindow::loadClicked()
{
    QString filePath;
    filePath = QFileDialog::getOpenFileName(0, "Select file", "", "All files (*)");

    if(!filePath.isEmpty())
    {
        QFile file(filePath);
        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            editor->setPlainText(file.readAll());
        }
    }
    else
    {
        qDebug() << "File selection cancelled by user";
    }
    //Show the opened file in the editor
}

void MainWindow::processClicked()
{
    QString word;
    int i = 0;
    int lenght = editor->toPlainText().length();
    QTextCursor myCursor = editor->textCursor();
    QRegularExpressionMatch match;

    int start = 0;
    int finish = 0;

    while(i <= lenght)
    {
        myCursor.setPosition(i); //Set cursor position
        myCursor.setPosition(i + 1, QTextCursor::KeepAnchor); // Select the character at the cursor position

        if(myCursor.selectedText() == " ")
        {
            //Presumably the end of a word; Compare to regeular expression
            qDebug() << "Space detected; Clear word";

            finish = i;
            finish--; //Current char is ' '; Previous char was end of word.

            //Compare to regulare expression
            for(int i=0; i<regularExpressionList.length(); i++)
            {
                match = regularExpressionList.at(i).match(word);
                if(match.hasMatch())
                {
                    this->boldWord(start, finish);
                    qDebug() << "Match: " << word;
                }
                else
                {
                    qDebug() << "NO match" << word;
                }
            }

            start = i;
            start++;

            word.clear();
        }
        else if(myCursor.selectedText() == "\u2029")
        {
            //Presumably the end of a word; Compare to regeular expression
            qDebug() << "Space detected; Clear word";

            finish = i;

            //Compare to regulare expression
            for(int i=0; i<regularExpressionList.length(); i++)
            {
                match = regularExpressionList.at(i).match(word);
                if(match.hasMatch())
                {
                    this->boldWord(start, finish);
                    qDebug() << "Match: " << word;
                }
                else
                {
                    qDebug() << "NO match" << word;
                }
            }

            start = i;
            start++;

            word.clear();
        }
        else if(i == lenght)
        {
            //End of the QTextEditor's text; Do not append; Compare word to regular expression


            finish = i;
            finish--; //Current char is ' '; Previous char was end of word.

            //Compare to regulare expression
            for(int i=0; i<regularExpressionList.length(); i++)
            {
                match = regularExpressionList.at(i).match(word);
                if(match.hasMatch())
                {
                    this->boldWord(start, finish);
                    qDebug() << "Match: " << word;
                }
                else
                {
                    qDebug() << "NO match: " << word;
                }
            }

            word.clear();
        }
        else
        {
            //Presumably a char; Append to word
            word.append(myCursor.selectedText());
            qDebug() << "Append char: " << myCursor.selectedText();

            finish = i;
        }

        i++; //QTextCursor will move out out range, intentionally.
    }

}

void MainWindow::boldWord(int startOfWord, int endfOfWord)
{
    QTextCursor formatCursor(document);

    formatCursor.setPosition(startOfWord);
    formatCursor.setPosition(endfOfWord, QTextCursor::KeepAnchor);

    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);

    formatCursor.mergeCharFormat(format); // Format text as bold
}


/*
 * emailRegex.setPattern("@");
        regularExpressionList.append(emailRegex);
    numberRegex0.setPattern("\b\d\d\d\-\d\d\d\-\d\d\d\b");
        regularExpressionList.append(numberRegex0);
    numberRegex1.setPattern("\b\d\d\d\-\d\d\d\d\d\d\b");
        regularExpressionList.append(numberRegex1);
    numberRegex2.setPattern("\b\d\d\d\d\d\d\d\d\d\b");
        regularExpressionList.append(numberRegex2);
    numberRegex3.setPattern("\b\(\d\d\d\\)-\d\d\d\d\d\d\b");
        regularExpressionList.append(numberRegex3);
    numberRegex4.setPattern("\b\(\d\d\d\)\d\d\d\d\d\d\b");
        regularExpressionList.append(numberRegex4);
        */
