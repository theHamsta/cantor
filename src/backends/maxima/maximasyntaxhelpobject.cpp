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
    Copyright (C) 2009-2012 Alexander Rieder <alexanderrieder@gmail.com>
 */

#include "maximasyntaxhelpobject.h"
#include "maximakeywords.h"

#include "maximasession.h"
#include "maximaexpression.h"

#include "result.h"

#include <kdebug.h>

MaximaSyntaxHelpObject::MaximaSyntaxHelpObject(const QString& cmd, MaximaSession* session) : Cantor::SyntaxHelpObject(cmd, session)
{
    m_expression=0;
}

MaximaSyntaxHelpObject::~MaximaSyntaxHelpObject()
{

}

void MaximaSyntaxHelpObject::fetchInformation()
{
    if(m_expression)
    {
        m_expression->setFinishingBehavior(Cantor::Expression::DeleteOnFinish);
    }

    bool isValid=false;
    foreach(const QString& func, MaximaKeywords::instance()->functions())
    {
        if(command()==func)
        {
            isValid=true;
            break;
        }
    }

    if(isValid)
    {
        //use the lisp command, instead of directly calling the
        //maxima function "describe" to avoid generating a new
        //output label that would mess up history
        QString cmd=":lisp(cl-info::info-exact \"%1\")";

        m_expression=session()->evaluateExpression(cmd.arg(command()));

        connect(m_expression, SIGNAL(statusChanged(Cantor::Expression::Status)), this, SLOT(expressionChangedStatus(Cantor::Expression::Status)));

    }else
    {
        kDebug()<<"invalid syntax request";
        emit done();
    }
}

void MaximaSyntaxHelpObject::expressionChangedStatus(Cantor::Expression::Status status)
{
    if(status==Cantor::Expression::Done)
    {
        kDebug()<<"expr done";
        if (!m_expression->hasResults())
            return;
        QString text=m_expression->results().at(0)->toHtml();
        QStringList lines=text.split('\n');

        QString syntax;
        foreach(QString line, lines) // krazy:exclude=foreach
        {
            line=line.trimmed();
            if(line.endsWith('\r'))
                line.chop(1);
            if(line.startsWith(QLatin1String("-- Function:")))
            {
                line.remove("-- Function:");
                line.remove("<br/>");
                syntax+=line.trimmed()+'\n';
            }else
                 break;
        }

        setHtml("<p style='white-space:pre'>"+syntax+"</p>");
        emit done();

        m_expression->deleteLater();
        m_expression=0;
    }else
    {
        kDebug()<<"not done: "<<status;
    }
}

