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
    Copyright (C) 2016 Ivan Lakhtanov <ivan.lakhtanov@gmail.com>
 */
#include "juliaexpression.h"

#include <QDir>
#include <QUuid>

#include "settings.h"
#include "juliasession.h"
#include "juliakeywords.h"
#include "textresult.h"
#include "imageresult.h"

JuliaExpression::JuliaExpression(Cantor::Session *session, bool internal)
    : Cantor::Expression(session, internal)
{
}

void JuliaExpression::evaluate()
{
    setStatus(Cantor::Expression::Computing);
    auto juliaSession = static_cast<JuliaSession *>(session());

    juliaSession->enqueueExpression(this);
}

QString JuliaExpression::internalCommand()
{
    QString cmd = command();
    auto juliaSession = static_cast<JuliaSession *>(session());

    // Plots integration
    m_plot_filename.clear();
    if (juliaSession->integratePlots() && checkPlotShowingCommands()) {
        // Simply add plot saving command to the end of execution
        QStringList inlinePlotFormats;
        inlinePlotFormats << QLatin1String("svg");
        inlinePlotFormats << QLatin1String("eps");
        inlinePlotFormats << QLatin1String("png");

        auto inlinePlotFormat =
            inlinePlotFormats[JuliaSettings::inlinePlotFormat()];
        m_plot_filename = QDir::tempPath() +
            QString::fromLatin1("/cantor-julia-export-%1.%2")
                .arg(QUuid::createUuid().toString()).arg(inlinePlotFormat);

        QString saveFigCommand =
            QString::fromLatin1("\nGR.savefig(\"%1\")\n").arg(m_plot_filename);

        cmd = cmd.append(saveFigCommand);
    }

    return cmd;
}

void JuliaExpression::finalize(const QString& output, const QString& error, bool wasException)
{
    if (wasException) {
        setErrorMessage(error);
        if (!output.isEmpty())
            setResult(new Cantor::TextResult(output));
        setStatus(Cantor::Expression::Error);
    } else {
        if (!m_plot_filename.isEmpty()
                && QFileInfo(m_plot_filename).exists()) {
            // If we have plot in result, show it
            setResult(
                new Cantor::ImageResult(QUrl::fromLocalFile(m_plot_filename)));
            QDir().remove(m_plot_filename);
        } else {
            if (!output.isEmpty())
                setResult(new Cantor::TextResult(output));
        }
        setStatus(Cantor::Expression::Done);
    }
}

void JuliaExpression::interrupt()
{
    setStatus(Cantor::Expression::Interrupted);
}

bool JuliaExpression::checkPlotShowingCommands()
{
    for (auto showingCommand :
            JuliaKeywords::instance()->plotShowingCommands()) {
        if (command().contains(showingCommand + QLatin1String("("))) {
            return true;
        }
    }
    return false;
}

