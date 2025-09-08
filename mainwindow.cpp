#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Jasur/Documents/togo/database/lab2(ПБЗ).db");

    if (db.open())
    {

        // Включение поддержки внешних ключей
        QSqlQuery enableForeignKeys(db);
        if (enableForeignKeys.exec("PRAGMA foreign_keys = ON")) {
            qDebug() << "Поддержка внешних ключей включена успешно";
        } else {
            qDebug() << "Ошибка при включении поддержки внешних ключей:" << enableForeignKeys.lastError().text();
        }



        ui->statusbar->showMessage("Падключон к бд." + db.lastError().databaseText());

        //Таблица "Выставочные Залы"

        model = new QSqlTableModel(this, db);
        model->setTable("Owners");
        model->select();

         ui->Owners->setModel(model);
         ui->Owners->setColumnHidden(0,true);

        //Таблица "Владельцы"

        model_2 = new QSqlTableModel(this, db);
        model_2->setTable("ExhibitionHalls");
        model_2->select();

        ui->ExhibitionHalls->setModel(model_2);
        ui->ExhibitionHalls->setColumnHidden(0,true);

        //Таблица "Художники"

        model_3 = new QSqlTableModel(this, db);
        model_3->setTable("Artists");
        model_3->select();

        ui->Artists->setModel(model_3);
        ui->Artists->setColumnHidden(0,true);

        //Таблица "Работы Художников"

        model_4 = new QSqlTableModel(this, db);
        model_4->setTable("Artworks");
        model_4->select();

        ui->Artworks->setModel(model_4);
        ui->Artworks->setColumnHidden(0,true);

        //Таблица "Участники Выставок"

        model_5 = new QSqlTableModel(this, db);
        model_5->setTable("ExhibitionParticipants");
        model_5->select();

        ui->ExhibitionParticipants->setModel(model_5);


        //Таблица "Выставки"

        model_6 = new QSqlTableModel(this, db);
        model_6->setTable("Exhibitions");
        model_6->select();

        ui->Exhibitions->setModel(model_6);
        ui->Exhibitions->setColumnHidden(0,true);

        //ComboBox

        connect(ui->filter_input, SIGNAL(activated(const QString &)), this, SLOT(on_filter_input_activated(const QString &)));
        //connect(ui->filter_input, QOverload<const QString&>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_filter_input_activated);

        fillBirthdateComboBox();

        //filter select two для третиго запроса
        connect(ui->filter_select_one, SIGNAL(activated(const QString &)), this, SLOT(on_filter_input_activated(const QString &)on_filter_select_one_activated(const QString &)));

        filter_select_one();

    }
    else
    {
        ui->statusbar->showMessage("Error connect for db.");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


//Функция для обналения страниц.
void MainWindow::updateAllModels() {
    model->select();
    model_2->select();
    model_3->select();
    model_4->select();
    model_5->select();
    model_6->select();
}




//Функфии добавления
void MainWindow::on_btn_add_clicked()
{
    model->insertRow(model->rowCount());
}


void MainWindow::on_btn_add_1_clicked()
{
    model_2->insertRow(model_2->rowCount());
}


void MainWindow::on_btn_add_2_clicked()
{
    model_3->insertRow(model_3->rowCount());
}


void MainWindow::on_btn_add_3_clicked()
{
    model_4->insertRow(model_4->rowCount());
}


void MainWindow::on_btn_add_4_clicked()
{
    model_5->insertRow(model_5->rowCount());
}


void MainWindow::on_btn_add_5_clicked()
{
    model_6->insertRow(model_6->rowCount());
}

//Конец функции



//фунции для удаления записи
void MainWindow::on_btn_remove_clicked()
{
    model->removeRow(currentRow);
    model->select();
}

//функция для получения id записа.(таблитца номер-1)
void MainWindow::on_Owners_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}

//таблитца номер-2
void MainWindow::on_btn_remove_1_clicked()
{
    model_2->removeRow(currentRow);
    model_2->select();
}


void MainWindow::on_ExhibitionHalls_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}

//таблитца номер-3

void MainWindow::on_btn_remove_2_clicked()
{
    model_3->removeRow(currentRow);
    model_3->select();
}


void MainWindow::on_Artists_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}

//таблитца номер-4

void MainWindow::on_btn_remove_3_clicked()
{
    model_4->removeRow(currentRow);
    model_4->select();
}


void MainWindow::on_Artworks_activated(const QModelIndex &index)
{
    currentRow = index.row();
}

//таблитца номер-5

void MainWindow::on_btn_remove_4_clicked()
{
    model_5->removeRow(currentRow);
    model_5->select();
}


void MainWindow::on_ExhibitionParticipants_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}

//таблитца номер-6

void MainWindow::on_btn_remove_5_clicked()
{
    model_6->removeRow(currentRow);
    model_6->select();
}


void MainWindow::on_Exhibitions_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}




void MainWindow::on_update_btn_clicked()
{
    QSqlQueryModel *exhibitionModel = new QSqlQueryModel(this);
    QSqlQuery query;

    query.prepare("SELECT ExhibitionHalls.hall_id, ExhibitionHalls.name AS hall_name, "
                  "ExhibitionHalls.city, ExhibitionHalls.address, ExhibitionHalls.phone AS hall_phone, "
                  "ExhibitionHalls.area, "
                  "Exhibitions.date AS exhibition_date "
                  "FROM ExhibitionHalls "
                  "JOIN Owners ON ExhibitionHalls.owner_id = Owners.owner_id "
                  "LEFT JOIN Exhibitions ON ExhibitionHalls.hall_id = Exhibitions.hall_id");

    if (query.exec()) {
        exhibitionModel->setQuery(query);

        // Настройка заголовков столбцов для QTableView
        exhibitionModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Зала"));
        exhibitionModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Название Зала"));
        exhibitionModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Город"));
        exhibitionModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Адрес Зала"));
        exhibitionModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Телефон Зала"));
        exhibitionModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Площадь Зала"));
        exhibitionModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Дата Выставки"));

        // Установка модели в QTableView
        ui->filter->setModel(exhibitionModel);
        ui->filter->setColumnHidden(0, true);

        // Настройка отображения данных
        ui->filter->horizontalHeader()->setStretchLastSection(true);
        ui->filter->resizeColumnsToContents();

       } else {
           qDebug() << "Ошибка выполнения SQL-запроса:" << query.lastError().text();
       }
}


// Ваш слот для заполнения выпадающего списка
void MainWindow::fillBirthdateComboBox() {
    QSqlQuery query("SELECT DISTINCT Exhibitions.name FROM Exhibitions ORDER BY name");
        while (query.next()) {
            QString exhibitionName = query.value(0).toString();
            ui->filter_input->addItem(exhibitionName);
        }
}



void MainWindow::on_filter_input_activated(const QString &exhibitionName)
{
    QSqlQueryModel *exhibitionModel = new QSqlQueryModel(this);
    QSqlQuery query;

    query.prepare("SELECT Exhibitions.name AS exhibition_name, Exhibitions.date AS exhibition_date, "
                  "Artworks.title AS artwork_title, Artworks.execution_type, "
                  "Artists.name AS artist_name, Artists.birth_date AS artist_birth_date, "
                  "Artworks.creation_date AS artwork_creation_date "
                  "FROM ExhibitionParticipants "
                  "JOIN Exhibitions ON ExhibitionParticipants.exhibition_id = Exhibitions.exhibition_id "
                  "JOIN Artworks ON ExhibitionParticipants.artist_id = Artworks.artist_id "
                  "JOIN Artists ON Artworks.artist_id = Artists.artist_id "
                  "WHERE Exhibitions.name = :exhibitionName");

    query.bindValue(":exhibitionName", exhibitionName);

    if (query.exec()) {
        exhibitionModel->setQuery(query);

        // Настройка заголовков столбцов для QTableView
        exhibitionModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Название Выставки"));
        exhibitionModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Дата Выставки"));
        exhibitionModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Название Работы"));
        exhibitionModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Тип Исполнения"));
        exhibitionModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Имя Художника"));
        exhibitionModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Дата Рождения Художника"));
        exhibitionModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Дата Создания Работы"));

        // Установка модели в QTableView
        ui->filter_one->setModel(exhibitionModel);

        // Настройка отображения данных
        ui->filter_one->horizontalHeader()->setStretchLastSection(true);
        ui->filter_one->resizeColumnsToContents();
    } else {
        qDebug() << "Ошибка выполнения SQL-запроса:" << query.lastError().text();
    }
}


void MainWindow::on_update_all_clicked()
{
    updateAllModels();
}


//3-запрос -Просмотр перечня выставок, проходящих в городе с адресами залов на текущий момент – дата,
//список – название выставки, адрес зала.


void MainWindow::filter_select_one()
{
    QSqlQuery cityQuery("SELECT DISTINCT ExhibitionHalls.city FROM ExhibitionHalls ORDER BY city");
    while (cityQuery.next()) {
        QString cityName = cityQuery.value(0).toString();
        ui->filter_select_one->addItem(cityName);
    }
}


void MainWindow::on_filter_select_one_activated(const QString &selectedCity)
{
    QSqlQueryModel *comboBoxModel = new QSqlQueryModel(this);
       QSqlQuery query;

       query.prepare("SELECT Exhibitions.date AS exhibition_date, "
                     "Exhibitions.name AS exhibition_name, "
                     "ExhibitionHalls.address AS hall_address "
                     "FROM Exhibitions "
                     "JOIN ExhibitionHalls ON Exhibitions.hall_id = ExhibitionHalls.hall_id "
                     "WHERE ExhibitionHalls.city = :city "
                     "AND Exhibitions.date >= CURRENT_DATE");

       query.bindValue(":city", selectedCity);

       if (query.exec()) {
           comboBoxModel->setQuery(query);

           // Настройка заголовков столбцов для QTableView
           comboBoxModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Дата Выставки"));
           comboBoxModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Название Выставки"));
           comboBoxModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Адрес Зала"));

           // Установка модели в QTableView
           ui->filter_two->setModel(comboBoxModel);

           // Настройка отображения данных
           ui->filter_two->horizontalHeader()->setStretchLastSection(true);
           ui->filter_two->resizeColumnsToContents();
       } else {
           qDebug() << "Ошибка выполнения SQL-запроса:" << query.lastError().text();
       }
}

