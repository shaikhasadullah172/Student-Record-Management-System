#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentIndex(0)
{
    ui->setupUi(this);

    // Teacher Requirement: Start mein Update aur Delete disable honge, Add enabled hoga[cite: 1]
    ui->pushButton_2->setEnabled(false); // Update button
    ui->pushButton_3->setEnabled(false); // Delete button
    ui->pushButton->setEnabled(true);    // Add button

    loadRecords();
    this->setStyleSheet("background-color: ##e3f2fd;"); // Light Blue background
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 1. ADD BUTTON LOGIC
void MainWindow::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    QString fatherName = ui->lineEdit->text();
    QString caste = ui->lineEdit_2->text();
    QString rollNo = ui->lineEdit_3->text();
    QString gpa = ui->lineEdit_4->text();

    if(name.isEmpty() || rollNo.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill required fields!");
        return;
    }

    QFile file("students.txt");
    if(file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << name << "," << caste << "," << fatherName << "," << rollNo << "," << gpa << "\n";
        file.close();
        QMessageBox::information(this, "Success", "Record added successfully!");

        // Clear fields
        ui->lineEdit->clear();
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        loadRecords();
    }
}

// Load records from file into vector
void MainWindow::loadRecords() {
    studentList.clear();
    QFile file("students.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if(parts.size() >= 5) {
                studentList.push_back({parts[0], parts[1], parts[2], parts[3], parts[4]});
            }
        }
        file.close();
    }
}

// 2. UPDATE BUTTON LOGIC
void MainWindow::on_pushButton_2_clicked()
{
    if (studentList.empty() || currentIndex <= 0 || currentIndex > studentList.size()) {
        QMessageBox::warning(this, "Error", "No record selected to update!");
        return;
    }

    int indexToUpdate = currentIndex - 1; // Correct index for current viewing record

    // Text boxes se naya data le kar vector mein update karo
    studentList[indexToUpdate].name = ui->lineEdit->text();
    studentList[indexToUpdate].fatherName = ui->lineEdit_2->text();
    studentList[indexToUpdate].caste = ui->lineEdit_3->text();
    studentList[indexToUpdate].rollNo = ui->lineEdit_4->text();
    studentList[indexToUpdate].gpa = ui->lineEdit_5->text();

    // Poori file ko updated vector ke sath rewrite karo
    QFile file("students.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto &s : studentList) {
            out << s.name << "," << s.caste << "," << s.fatherName << "," << s.rollNo << "," << s.gpa << "\n";
        }
        file.close();
        QMessageBox::information(this, "Success", "Record updated successfully!");
    }
}

// 3. DELETE BUTTON LOGIC
void MainWindow::on_pushButton_3_clicked()
{
    if (studentList.empty() || currentIndex <= 0 || currentIndex > studentList.size()) {
        QMessageBox::warning(this, "Error", "No record selected to delete!");
        return;
    }

    int indexToDelete = currentIndex - 1;
    studentList.erase(studentList.begin() + indexToDelete); // Vector se remove karo

    // Poori file ko rewrite karo taake deleted record nikal jaye
    QFile file("students.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto &s : studentList) {
            out << s.name << "," << s.caste << "," << s.fatherName << "," << s.rollNo << "," << s.gpa << "\n";
        }
        file.close();
    }

    QMessageBox::information(this, "Success", "Record deleted successfully!");

    // Fields clear karo aur index reset karo
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    currentIndex = 0;

    // Wapas Add mode par aa jao
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}
void MainWindow::on_pushButton_4_clicked()
{
    if(studentList.empty()) {
        QMessageBox::information(this, "Empty", "No records found in file.");
        return;
    }

    // Teacher requirement: Next mode mein Add disable aur Update/Delete enable hote hain[cite: 1]
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);

    if(currentIndex < studentList.size()) {
        ui->lineEdit->setText(studentList[currentIndex].name);
        ui->lineEdit_2->setText(studentList[currentIndex].caste);
        ui->lineEdit->setText(studentList[currentIndex].fatherName);
        ui->lineEdit_3->setText(studentList[currentIndex].rollNo);
        ui->lineEdit_4->setText(studentList[currentIndex].gpa);

        currentIndex++;
    } else {
        currentIndex = 0;
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        QMessageBox::information(this, "End", "Reached end of records. Restarting from first.");
    }
}