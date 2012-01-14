/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in 
** accordance with the Qt Commercial License Agreement provided with
** the Software or, alternatively, in accordance with the terms
** contained in a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QVERSITDOCUMENTWRITER_H
#define QVERSITDOCUMENTWRITER_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qversitproperty.h"
#include <QByteArray>
#include <QMultiHash>

QT_BEGIN_NAMESPACE
class QIODevice;
class QTextCodec;
class QTextEncoder;
QT_END_NAMESPACE

QTM_BEGIN_NAMESPACE

class QM_AUTOTEST_EXPORT QVersitDocumentWriter
{
public:
    QVersitDocumentWriter(QVersitDocument::VersitType type);
    virtual ~QVersitDocumentWriter();

    void setCodec(QTextCodec* codec);
    void setDevice(QIODevice* device);

    virtual void encodeVersitProperty(const QVersitProperty& property) = 0;
    virtual void encodeParameters(const QMultiHash<QString,QString>& parameters) = 0;
    bool encodeVersitDocument(const QVersitDocument& document, bool encodeVersion = true);
    void encodeGroupsAndName(const QVersitProperty& property);

    void writeBytes(const QByteArray& value);
    void writeString(const QString& value, bool useUtf8 = false);
    void writeCrlf();

protected:
    QVersitDocument::VersitType mType;
    QIODevice* mDevice;
    QTextCodec* mCodec;
    bool mCodecIsAsciiCompatible;
    QTextEncoder* mEncoder;
    QTextEncoder* mUtf8Encoder;
    bool mSuccessful;
    int mCurrentLineLength;
};

QTM_END_NAMESPACE

#endif // QVERSITDOCUMENTWRITER_H