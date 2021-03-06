/**
 * CarBudget, Sailfish application to manage car cost
 *
 * Copyright (C) 2014 Fabien Proriol
 *
 * This file is part of CarBudget.
 *
 * CarBudget is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * CarBudget is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with CarBudget. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Fabien Proriol
 */


#include "fueltype.h"
#include "car.h"

Fueltype::Fueltype(QObject *parent) :
    QObject(parent),
    _id(0),
    _name("Not Set")
{
}

Fueltype::Fueltype(unsigned int id, QString name, Car *parent):
    QObject(parent),
    _car(parent),
    _id(id),
    _name(name)
{
}

unsigned int Fueltype::id() const
{
    return _id;
}

void Fueltype::setId(unsigned int id)
{
    _id = id;
    emit idChanged();
}

QString Fueltype::name() const
{
    return _name;
}

void Fueltype::setName(QString name)
{
    _name = name;
    emit nameChanged();
}

void Fueltype::save()
{
    if(_id < 0)
    {

        QSqlQuery query(_car->db);
        QString sql = QString("INSERT INTO FueltypeList (id,name) VALUES(NULL,'%1')").arg(_name);
        if(query.exec(sql))
        {
            _id = query.lastInsertId().toInt();
            qDebug() << "Create Fueltype in database with id " << _id << "and value " << _name;
            _car->db.commit();
        }
        else
        {
            qDebug() << "Error during Create Fueltype in database";
            qDebug() << query.lastError();
        }
    }
    else
    {
        QSqlQuery query(_car->db);
        QString sql = QString("UPDATE FueltypeList SET name='%1' WHERE id=%2;").arg(_name).arg(_id);
        qDebug() << sql;
        if(query.exec(sql))
        {
            qDebug() << "Update Fueltype in database with id " << _id;
            _car->db.commit();
        }
        else
        {
            qDebug() << "Error during Update Fueltype in database";
            qDebug() << query.lastError();
        }
    }
}
