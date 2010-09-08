/*
    Copyright (C) 2010 Miha Čančula <miha.cancula@gmail.com>

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
*/

#ifndef OCTAVESYNTAXHELPOBJECT_H
#define OCTAVESYNTAXHELPOBJECT_H

#include <syntaxhelpobject.h>

namespace Cantor
{
    class Expression;
}

class OctaveSyntaxHelpObject : public Cantor::SyntaxHelpObject
{
  Q_OBJECT
  public: 
    OctaveSyntaxHelpObject(const QString& command, Cantor::Session* session);
    virtual ~OctaveSyntaxHelpObject();

protected:
    virtual void fetchInformation();
    
  private Q_SLOTS:
    void fetchingDone();
    
  private:
    Cantor::Expression* m_expression;
};

#endif // OCTAVESYNTAXHELPOBJECT_H