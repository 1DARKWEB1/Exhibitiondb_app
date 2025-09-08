#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//библиотеки для бд.
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTableView>
#include <QMainWindow>
#include <QDate>
#include <QStandardItemModel>

#include <QSqlQuery>
#include <QtSql/QSqlError>
#include <QtDebug>

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
    void on_btn_add_clicked();

    void on_btn_add_1_clicked();

    void on_btn_add_2_clicked();

    void on_btn_add_3_clicked();

    void on_btn_add_5_clicked();

    void on_btn_add_4_clicked();

    void on_btn_remove_clicked();

    void on_Owners_clicked(const QModelIndex &index);

    void on_btn_remove_1_clicked();

    void on_ExhibitionHalls_clicked(const QModelIndex &index);

    void on_btn_remove_2_clicked();

    void on_Artists_clicked(const QModelIndex &index);

    void on_btn_remove_3_clicked();

    void on_Artworks_activated(const QModelIndex &index);

    void on_btn_remove_4_clicked();

    void on_ExhibitionParticipants_clicked(const QModelIndex &index);

    void on_btn_remove_5_clicked();

    void on_Exhibitions_clicked(const QModelIndex &index);

    void on_update_btn_clicked();


    void fillBirthdateComboBox();


    void on_filter_input_activated(const QString &arg1);

    void on_update_all_clicked();

    void updateAllModels();


    void filter_select_one();

    void on_filter_select_one_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlTableModel *model_2;
    QSqlTableModel *model_3;
    QSqlTableModel *model_4;
    QSqlTableModel *model_5;
    QSqlTableModel *model_6;

    QSqlTableModel *exhibitionModel;

    QSqlTableModel *datemodel;

    QSqlTableModel *comboBoxModel;

    int currentRow;


};
#endif // MAINWINDOW_H
