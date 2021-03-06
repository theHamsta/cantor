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

#ifndef _SAGEEXPRESSION_H
#define _SAGEEXPRESSION_H

#include "expression.h"

class SageExpression : public Cantor::Expression
{
  Q_OBJECT
  public:
    explicit SageExpression(Cantor::Session*, bool internal = false);

    void evaluate() override;
    void interrupt() override;

    void parseOutput(const QString&);
    void parseError(const QString&);

    void addFileResult(const QString&);

    void onProcessError(const QString&);

  public Q_SLOTS:
    void evalFinished();

  protected:
    QString additionalLatexHeaders() override;

  private:
    QString m_outputCache;
    QString m_imagePath;
    bool m_isHelpRequest;
    int m_promptCount;
    bool m_syntaxError;
};

#endif /* _SAGEEXPRESSION_H */
