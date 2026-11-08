#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>

using namespace std;

struct Student {
    QString name;
    QString caste;
    QString fatherName;
    QString rollNo;
    QString gpa;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();   // Add Button
    void on_pushButton_2_clicked(); // Update Button
    void on_pushButton_3_clicked(); // Delete Button
    void on_pushButton_4_clicked(); // Next Button

private:
    Ui::MainWindow *ui;
    void loadRecords();
    vector<Student> studentList;
    int currentIndex;
};
#endif // MAINWINDOW_H