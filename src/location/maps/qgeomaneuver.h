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

#ifndef QGEOMANEUVER_H
#define QGEOMANEUVER_H

#include "qmobilityglobal.h"

#include <QExplicitlySharedDataPointer>

class QString;

QT_BEGIN_HEADER

QTM_BEGIN_NAMESPACE

class QGeoCoordinate;
class QGeoManeuverPrivate;

class Q_LOCATION_EXPORT QGeoManeuver
{

public:
    enum InstructionDirection {
        NoDirection,
        DirectionForward,
        DirectionBearRight,
        DirectionLightRight,
        DirectionRight,
        DirectionHardRight,
        DirectionUTurnRight,
        DirectionUTurnLeft,
        DirectionHardLeft,
        DirectionLeft,
        DirectionLightLeft,
        DirectionBearLeft
    };

    QGeoManeuver();
    QGeoManeuver(const QGeoManeuver &other);
    ~QGeoManeuver();

    QGeoManeuver& operator= (const QGeoManeuver &other);

    bool operator== (const QGeoManeuver &other) const;
    bool operator!= (const QGeoManeuver &other) const;

    bool isValid() const;

    void setPosition(const QGeoCoordinate &position);
    QGeoCoordinate position() const;

    void setInstructionText(const QString &instructionText);
    QString instructionText() const;

    void setDirection(InstructionDirection direction);
    InstructionDirection direction() const;

    void setTimeToNextInstruction(int secs);
    int timeToNextInstruction() const;

    void setDistanceToNextInstruction(qreal distance);
    qreal distanceToNextInstruction() const;

    void setWaypoint(const QGeoCoordinate &coordinate);
    QGeoCoordinate waypoint() const;

private:
    QExplicitlySharedDataPointer<QGeoManeuverPrivate> d_ptr;
};

QTM_END_NAMESPACE

QT_END_HEADER

#endif
