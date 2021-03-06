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
    Copyright (C) 2009 Alexander Rieder <alexanderrieder@gmail.com>
 */

#ifndef _IMAGERESULT_H
#define _IMAGERESULT_H

#include "result.h"
#include <QUrl>
#include <QSize>

class QImage;

namespace Cantor
{
class ImageResultPrivate;

class CANTOR_EXPORT ImageResult : public Result
{
  public:
    enum{Type=2};
    explicit ImageResult( const QUrl& url, const QString& alt=QString());
    explicit ImageResult( const QImage& image, const QString& alt=QString());
    ~ImageResult() override;

    QString toHtml() override;
    QString toLatex() override;
    QVariant data() override;
    QUrl url() override;

    int type() override;
    QString mimeType() override;

    QSize displaySize();
    void setDisplaySize(QSize size);

    QString originalFormat();
    void setOriginalFormat(const QString& format);
    void setSvgContent(const QString& svgContent);

    QDomElement toXml(QDomDocument& doc) override;
    QJsonValue toJupyterJson() override;
    void saveAdditionalData(KZip* archive) override;

    void save(const QString& filename) override;

  private:
    ImageResultPrivate* d;
};

}

#endif /* _IMAGERESULT_H */
