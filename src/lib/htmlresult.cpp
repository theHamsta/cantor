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
    Copyright (C) 2019 Sirgienko Nikita <warquark@gmail.com>
 */

#include "htmlresult.h"

#include <QFile>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonObject>

using namespace Cantor;

class Cantor::HtmlResultPrivate
{
public:
    QString html;
    QString plain;
    Cantor::HtmlResult::Format format{Cantor::HtmlResult::Html};
};

HtmlResult::HtmlResult(const QString& html, const QString& plain) : d(new HtmlResultPrivate())
{
    d->html = html;
    d->plain = plain;
}

HtmlResult::~HtmlResult()
{
    delete d;
}

QString HtmlResult::toHtml()
{
    switch(d->format)
    {
        case HtmlResult::Html:
            return d->html;

        case HtmlResult::HtmlSource:
            return QStringLiteral("<code><pre>") + d->html.toHtmlEscaped() + QStringLiteral("</pre></code>");

        case HtmlResult::PlainAlternative:
            return QStringLiteral("<pre>") + d->plain.toHtmlEscaped() + QStringLiteral("</pre>");

        default:
            return QString();
    }
}

QVariant Cantor::HtmlResult::data()
{
    return d->html;
}

QString Cantor::HtmlResult::plain()
{
    return d->plain;
}

void Cantor::HtmlResult::setFormat(HtmlResult::Format format)
{
    d->format = format;
}

HtmlResult::Format Cantor::HtmlResult::format()
{
    return d->format;
}

int Cantor::HtmlResult::type()
{
    return HtmlResult::Type;
}

QString Cantor::HtmlResult::mimeType()
{
    return QStringLiteral("text/html");
}

QDomElement Cantor::HtmlResult::toXml(QDomDocument& doc)
{
    QDomElement e=doc.createElement(QStringLiteral("Result"));
    e.setAttribute(QStringLiteral("type"), QStringLiteral("html"));
    switch(d->format)
    {
        case HtmlResult::HtmlSource:
            e.setAttribute(QStringLiteral("format"), QStringLiteral("htmlSource"));

        case HtmlResult::PlainAlternative:
            e.setAttribute(QStringLiteral("format"), QStringLiteral("plain"));
    }

    QDomElement plainE = doc.createElement(QStringLiteral("Plain"));
    plainE.appendChild(doc.createTextNode(d->plain));
    e.appendChild(plainE);

    QDomElement htmlE = doc.createElement(QStringLiteral("Html"));
    htmlE.appendChild(doc.createTextNode(d->html));
    e.appendChild(htmlE);

    return e;
}

QJsonValue Cantor::HtmlResult::toJupyterJson()
{
    QJsonObject root;
    root.insert(QLatin1String("output_type"), QLatin1String("display_data"));

    QJsonObject data;
    data.insert(QLatin1String("text/html"), jupyterText(d->html));
    if (!d->plain.isEmpty())
        data.insert(QLatin1String("text/plain"), jupyterText(d->plain));
    root.insert(QLatin1String("data"), data);

    root.insert(QLatin1String("metadata"), QJsonObject());

    return root;
}

void Cantor::HtmlResult::save(const QString& filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream stream(&file);

    stream<<d->html;

    file.close();
}


QJsonArray Cantor::HtmlResult::jupyterText(const QString& text)
{
    QJsonArray array;

    const QStringList& lines = text.split(QLatin1Char('\n'));
    for (int i = 0; i < lines.size(); i++)
    {
        QString line = lines[i];
        if (i != lines.size() - 1) // not last
            line.append(QLatin1Char('\n'));
        array.append(line);
    }

    return array;
}