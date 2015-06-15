//
// Created by NiL on 15/4/8.
//

#ifndef _TESTPROJECT_MODEL_H_
#define _TESTPROJECT_MODEL_H_

#include <QMap>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <vector>

#include "Connection.h"

using namespace std;

/*
* 数据库模型类
*
* 所有的数据库模型都将继承这个类
*/

template<class T>
class Model {
public:
    // 设置内部的数据库连接
    static void setConnection(Connection * connection);
    // 获取存储的大小
    static int size();
    // 根据ID查找一个Model实例
    static T findById(int t_id);
    static vector<T> findByField(QString field, QString value);
    static vector<T> findAllWithOrder(QString order);
    static vector<T> findAll();

    // 设置某一个字段的值
    bool set(QString key, QString value);
    bool set(QString key, int number);
    // 获取某一个字段的值
    QString get(QString key);
    int getId();
    // 保存数据到数据库
    bool save();
    // 对已经保存的字段进行更新
    bool update();
    void setId(int t_id);
    bool isEmpty();

protected:
    // 当前模型的表名
    static QString tableName;
    // 当前模型的字段
    static QMap<QString, QString> fields;
    // 当前模型的主键
    static QString primaryKey;
    // 数据库连接
    static Connection *connection;

    // 实例的字段数据
    QMap<QString, QString> map;

    // 建表方法，仅仅在数据库为空的时候调用
    void createTable();
    // 保存主键数据
    int id = -1;
};
template <class T> Connection * Model<T>::connection = NULL;

template <class T> void Model<T>::setConnection(Connection *t_connection) {
    connection = t_connection;
}

template <class T> void Model<T>::createTable() {
    if (connection->isTableExist(tableName)) {
        return;
    }

    QSqlQuery query(connection->db);
    QString queryString = "Create TABLE " + tableName;
    QString fieldString = "";
    fieldString += primaryKey;
    fieldString += " INTEGER PRIMARY KEY AUTOINCREMENT, ";

    for (auto key : fields.keys()) {
        fieldString += key;
        fieldString += " ";
        fieldString += fields.value(key);
        fieldString += ", ";
    }
    fieldString.remove(fieldString.length()-2, 2);
    fieldString = " ( " + fieldString + " )";
    queryString += fieldString;
    qDebug() << queryString;

    query.exec(queryString);
    qDebug() << "Model:: create table " << tableName << " success";
}

template <class T> int Model<T>::size() {
    QSqlQuery query;
    QString queryString;
    queryString = "SELECT COUNT(*) from " + tableName;
    query.exec(queryString);
    query.next();
    return query.value(0).toInt();
}

template <class T> int Model<T>::getId() { return id; }

template <class T> bool Model<T>::set(QString key, QString value) {
    if (fields.find(key) == fields.end()) {
        //没有找到
        qDebug() << "Model: key" << key << "not found";
        return false;
    }
    map[key] = value;
    return true;
}

template <class T> bool Model<T>::set(QString key, int number) {
    return set(key, QString::number(number));
}

template <class T> QString Model<T>::get(QString key) {
    if (key == primaryKey) {
        return QString::number(id);
    } else {
        return map[key];
    }
}

template <class T> bool Model<T>::save() {
    if (!connection->isTableExist(tableName)) {
        createTable();
    }

    if (id != -1) {
        return update();
    }

    QSqlQuery query;
    QString queryString, fieldString;
    queryString = "INSERT INTO " + tableName;
    for (auto key : fields.keys()) {
        fieldString += key + ", ";
    }
    //移除多余的逗号啦
    fieldString.remove(fieldString.length()-2, 2);

    fieldString = " ( " +fieldString +" )";
    queryString += fieldString;

    fieldString = "";
    for (auto key : fields.keys()) {
        fieldString +=":" + key + ",";
    }

    fieldString.remove(fieldString.length()-1, 2);
    fieldString = " VALUES ( " + fieldString +" )";
    queryString += fieldString;

    query.prepare(queryString);

    for (auto key : fields.keys()) {
        query.bindValue(":" + key, map[key]);
    }
    query.exec();

    if (query.lastError().isValid()) {
        qDebug() << "Model::" + tableName + "INSERT ERROR:" << query.lastError();
        return false;
    }

    id = query.lastInsertId().toInt();
    return true;
}


template <class T> bool Model<T>::update() {
    QSqlQuery query;
    QString queryString, fieldString;
    queryString = "UPDATE " + tableName + " SET";

    for (auto key : fields.keys()) {
        fieldString += " " + key + " = :" + key + ", ";
    }
    fieldString.remove(fieldString.length()-2, 2);

    queryString += fieldString;
    queryString += " WHERE " + primaryKey + "= :" + primaryKey;

    query.prepare(queryString);
    for (auto key : fields.keys()) {
        query.bindValue(":" + key, map[key]);
    }
    query.bindValue(":" + primaryKey, id);
    query.exec();

    if (query.lastError().isValid()) {
        qDebug() << "Model::" + tableName + "UPDATE ERROR:" << query.lastError();
        return false;
    }
    return true;
}

template <class T> void Model<T>::setId(int t_id) {
    id = t_id;
}

template <class T> T Model<T>::findById(int t_id) {
    QSqlQuery query;
    QString queryString;
    queryString = "SELECT * FROM " + tableName + " WHERE " + primaryKey + " = " + QString::number(t_id);

    qDebug() << queryString;
    query.exec(queryString);
    query.next();
    T model;
    int i = 1;
    model.setId(query.value(0).toInt());
    for (auto key : fields.keys()) {
        model.set(key, query.value(i).toString());
        i++;
    }
    return model;
}


template <class T> vector<T> Model<T>::findByField(QString field, QString value) {
    vector<T> list;

    QSqlQuery query;
    QString queryString;
    queryString = "SELECT * FROM " + tableName + " WHERE " + field + " = " + ":field";
    query.prepare(queryString);
    query.bindValue(":field", value);
    query.exec();
    while(query.next()) {
        T model;
        int i = 1;
        model.setId(query.value(0).toInt());
        for (auto key : fields.keys()) {
            model.set(key, query.value(i).toString());
            i++;
        }
        list.push_back(model);
    }
    return list;
}

template <class T> vector<T> Model<T>::findAllWithOrder(QString order) {
    vector<T> list;

    QSqlQuery query;
    QString queryString;
    queryString = "SELECT * FROM " + tableName + " ORDER BY " + order;
    query.prepare(queryString);
    query.exec();
    while(query.next()) {
        T model;
        int i = 1;
        model.setId(query.value(0).toInt());
        for (auto key : fields.keys()) {
            model.set(key, query.value(i).toString());
            i++;
        }
        list.push_back(model);
    }
    return list;
}

template <class T> vector<T> Model<T>::findAll() {
    vector<T> list;

    QSqlQuery query;
    QString queryString;
    queryString = "SELECT * FROM " + tableName;
    query.prepare(queryString);
    query.exec();

    QString err = query.lastError().text();
    while(query.next()) {
        T model;
        int i = 1;
        model.setId(query.value(0).toInt());
        for (auto key : fields.keys()) {
            model.set(key, query.value(i).toString());
            i++;
        }
        list.push_back(model);
    }
    return list;
}




template <class T> bool Model<T>::isEmpty() {
    return id == -1;
}
#endif //_TESTPROJECT_MODEL_H_
