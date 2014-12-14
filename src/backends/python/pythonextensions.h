/*
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301, USA.

    ---
    Copyright (C) 2013 Filipe Saraiva <filipe@kde.org>
 */

#ifndef PYTHONEXTENSIONS_H
#define PYTHONEXTENSIONS_H

#include <extension.h>

#define PYTHON_EXT_CDTOR_DECL(name) Python##name##Extension(QObject* parent); \
                                    ~Python##name##Extension();

class PythonLinearAlgebraExtension : public Cantor::LinearAlgebraExtension
{
    public:
    PYTHON_EXT_CDTOR_DECL(LinearAlgebra)
    virtual QString createVector(const QStringList& entries, VectorType type);
    virtual QString nullVector(int size, VectorType type);
    virtual QString createMatrix(const Cantor::LinearAlgebraExtension::Matrix& matrix);
    virtual QString identityMatrix(int size);
    virtual QString nullMatrix(int rows, int columns);
    virtual QString rank(const QString& matrix);
    virtual QString invertMatrix(const QString& matrix);
    virtual QString charPoly(const QString& matrix);
    virtual QString eigenVectors(const QString& matrix);
    virtual QString eigenValues(const QString& matrix);
};

class PythonPackagingExtension : public Cantor::PackagingExtension
{
    public:
    PYTHON_EXT_CDTOR_DECL(Packaging)
    virtual QString importPackage(const QString& module);
};

class PythonPlotExtension : public Cantor::PlotExtension
{
    public:
    PYTHON_EXT_CDTOR_DECL(Plot)
    virtual QString plotFunction2d(const QString& function, const QString& variable, const QString& left, const QString& right);
    virtual QString plotFunction3d(const QString& function, VariableParameter var1, VariableParameter var2);
};

class PythonScriptExtension : public Cantor::ScriptExtension
{
    public:
        PYTHON_EXT_CDTOR_DECL(Script)
        virtual QString scriptFileFilter();
        virtual QString highlightingMode();
        virtual QString runExternalScript(const QString& path);
};

class PythonVariableManagementExtension : public Cantor::VariableManagementExtension
{
    public:
    PYTHON_EXT_CDTOR_DECL(VariableManagement)
    virtual QString addVariable(const QString& name, const QString& value);
    virtual QString setValue(const QString& name, const QString& value);
    virtual QString removeVariable(const QString& name);
    virtual QString saveVariables(const QString& fileName);
    virtual QString loadVariables(const QString& fileName);
    virtual QString clearVariables();
};

#endif // PYTHONEXTENSIONS_H