/*************************************************************************************
*  Copyright (C) 2009 by Aleix Pol <aleixpol@kde.org>                               *
*                                                                                   *
*  This program is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU General Public License                      *
*  as published by the Free Software Foundation; either version 2                   *
*  of the License, or (at your option) any later version.                           *
*                                                                                   *
*  This program is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    *
*  GNU General Public License for more details.                                     *
*                                                                                   *
*  You should have received a copy of the GNU General Public License                *
*  along with this program; if not, write to the Free Software                      *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA   *
*************************************************************************************/

#include "kalgebrasession.h"
#include "kalgebraexpression.h"
#include "kalgebratabcompletionobject.h"
#include <analitza/analitza.h>

KAlgebraSession::KAlgebraSession( Cantor::Backend* backend)
    : Session(backend)
{
    m_analitza = new Analitza::Analitza;
}

KAlgebraSession::~KAlgebraSession()
{
    delete m_analitza;
}

void KAlgebraSession::login()
{
    changeStatus(Cantor::Session::Done);
    emit ready();
}

void KAlgebraSession::logout()
{}

void KAlgebraSession::interrupt()
{
    foreach(Cantor::Expression* e, m_runningExpressions)
        e->interrupt();
    m_runningExpressions.clear();
    changeStatus(Cantor::Session::Done);
}

Cantor::Expression* KAlgebraSession::evaluateExpression(const QString& cmd,
                                                        Cantor::Expression::FinishingBehavior behave)
{
    KAlgebraExpression* expr=new KAlgebraExpression(this);
    expr->setFinishingBehavior(behave);
    connect(expr, SIGNAL(statusChanged(Cantor::Expression::Status)), this, SLOT(expressionFinished()));
    expr->setCommand(cmd);
    expr->evaluate();
    
    if(m_runningExpressions.isEmpty())
        changeStatus(Cantor::Session::Running);
    m_runningExpressions.append(expr);
    
    return expr;
}

Cantor::TabCompletionObject* KAlgebraSession::tabCompletionFor(const QString& command)
{
    return new KAlgebraTabCompletionObject(command, this);
}

void KAlgebraSession::expressionFinished()
{
    m_runningExpressions.removeAll(qobject_cast<KAlgebraExpression*>(sender()));
    if(m_runningExpressions.isEmpty())
        changeStatus(Cantor::Session::Done);
}
