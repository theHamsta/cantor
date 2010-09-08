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

#ifndef OCTAVEEXPRESSION_H
#define OCTAVEEXPRESSION_H

#include <expression.h>
#include <QStringList>


class OctaveExpression : public Cantor::Expression
{
    Q_OBJECT
    public:
	OctaveExpression(Cantor::Session* session);
	~OctaveExpression();
	virtual void interrupt();
	virtual void evaluate();
        void parseOutput ( QString output );
        void parseError(QString error);
	void parseEpsFile(QString file);

        void finalize();
	void setPlotPending(bool plot);

    private:
        QString m_resultString;
        int m_numberOfLines;
	bool m_plotPending;
	bool m_finished;
	bool m_error;
    QStringList m_plotCommands;

};

#endif // OCTAVEEXPRESSION_H