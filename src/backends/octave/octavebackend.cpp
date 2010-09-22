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

#include "octavebackend.h"
#include "octavesession.h"
#include "octaveextensions.h"
#include "settings.h"

#include "cantor_macros.h"

#include <QtCore/QFileInfo>
#include <QtGui/QWidget>

#include "ui_settings.h"

OctaveBackend::OctaveBackend(QObject* parent, const QList< QVariant > args): Backend(parent, args)
{
    kDebug();
    new OctaveHistoryExtension(this);
    new OctaveScriptExtension(this);
    new OctavePlotExtension(this);
    new OctaveLinearAlgebraExtension(this);
    new OctaveVariableManagementExtension(this);
}


QString OctaveBackend::id() const
{
    return "octave";
}

Cantor::Backend::Capabilities OctaveBackend::capabilities() const
{
    return SyntaxHighlighting | Completion | SyntaxHelp | VariableManagement;
}

Cantor::Session* OctaveBackend::createSession()
{
    kDebug();
    return new OctaveSession(this);
}

OctaveBackend::~OctaveBackend()
{
}

bool OctaveBackend::requirementsFullfilled() const
{
    return QFileInfo(OctaveSettings::path().toLocalFile()).isExecutable();
}

KUrl OctaveBackend::helpUrl() const
{
    return i18nc("the url to the documentation of Octave, please check if there is a translated version (currently Czech and Japanese) and use the correct url",
    "http://www.gnu.org/software/octave/doc/interpreter/");
}

QString OctaveBackend::description() const
{
    return i18n("GNU Octave is a high-level language, primarily intended for numerical computations. <br/>"
                "It provides a convenient command line interface for solving linear and nonlinear problems numerically, and for performing other numerical experiments using a language that is mostly compatible with Matlab.");
}

QWidget* OctaveBackend::settingsWidget(QWidget* parent) const
{
    QWidget* widget = new QWidget(parent);
    Ui::OctaveSettingsBase ui;
    ui.setupUi(widget);
    return widget;
}

KConfigSkeleton* OctaveBackend::config() const
{
    return OctaveSettings::self();
}

K_EXPORT_CANTOR_PLUGIN(octavebackend, OctaveBackend)

#include "octavebackend.moc"

