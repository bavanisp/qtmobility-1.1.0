/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <QtDeclarative/qdeclarativeextensionplugin.h>
#include <QtDeclarative/qdeclarative.h>
#include <QtDeclarative/qdeclarativeengine.h>
#include <QtDeclarative/qdeclarativecomponent.h>
#include "qsoundeffect_p.h"

#include "qdeclarativevideo_p.h"
#include "qdeclarativeaudio_p.h"
#include "qdeclarativemediametadata_p.h"
#include "qdeclarativecamera_p.h"
#include "qdeclarativecamerapreviewprovider_p.h"

QML_DECLARE_TYPE(QSoundEffect)

QT_BEGIN_NAMESPACE

class QMultimediaDeclarativeModule : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    virtual void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("QtMultimediaKit"));

        qmlRegisterType<QSoundEffect>(uri, 1, 1, "SoundEffect");
        qmlRegisterType<QDeclarativeAudio>(uri, 1, 1, "Audio");
#ifndef Q_OS_SYMBIAN
        qmlRegisterType<QDeclarativeVideo>(uri, 1, 1, "Video");
#else
        qmlRegisterUncreatableType<QDeclarativeVideo>(uri, 1, 1, "Video", "Type not supported in symbian");
#endif
        qmlRegisterType<QDeclarativeCamera>(uri, 1, 1, "Camera");
        qmlRegisterType<QDeclarativeMediaMetaData>();
    }

    void initializeEngine(QDeclarativeEngine *engine, const char *uri)
    {
        Q_UNUSED(uri);
        engine->addImageProvider("camera", new QDeclarativeCameraPreviewProvider);
    }
};

QT_END_NAMESPACE

#include "multimedia.moc"

Q_EXPORT_PLUGIN2(qmultimediadeclarativemodule, QT_PREPEND_NAMESPACE(QMultimediaDeclarativeModule));

