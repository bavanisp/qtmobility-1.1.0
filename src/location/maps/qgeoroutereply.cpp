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

#include "qgeoroutereply.h"
#include "qgeoroutereply_p.h"

QTM_BEGIN_NAMESPACE

/*!
    \class QGeoRouteReply

    \brief The QGeoRouteReply class manages an operation started by an instance
    of QGeoRoutingManager.

    \inmodule QtLocation

    \ingroup maps-routing

    Instances of QGeoRouteReply manage the state and results of these
    operations.

    The isFinished(), error() and errorString() methods provide information
    on whether the operation has completed and if it completed succesfully.

    The finished() and error(QGeoRouteReply::Error,QString)
    signals can be used to monitor the progress of the operation.

    It is possible that a newly created QGeoRouteReply may be in a finished
    state, most commonly because an error has occurred. Since such an instance
    will never emit the finished() or
    error(QGeoRouteReply::Error,QString) signals, it is
    important to check the result of isFinished() before making the connections
    to the signals. The documentation for QGeoRoutingManager demonstrates how
    this might be carried out.

    If the operation completes successfully the results will be able to be
    accessed with routes().
*/

/*!
    \enum QGeoRouteReply::Error

    Describes an error which prevented the completion of the operation.

    \value NoError
        No error has occurred.
    \value EngineNotSetError
        The routing manager that was used did not have a QGeoRoutingManagerEngine instance associated with it.
    \value CommunicationError
        An error occurred while communicating with the service provider.
    \value ParseError
        The response from the service provider was in an unrecognizable format.
    \value UnsupportedOptionError
        The requested operation or one of the options for the operation are not
        supported by the service provider.
    \value UnknownError
        An error occurred which does not fit into any of the other categories.
*/

/*!
    Constructs a route reply object based on \a request, with the specified \a parent.
*/
QGeoRouteReply::QGeoRouteReply(const QGeoRouteRequest &request, QObject *parent)
    : QObject(parent),
      d_ptr(new QGeoRouteReplyPrivate(request))
{
}

/*!
    Constructs a route reply with a given \a error and \a errorString and the specified \a parent.
*/
QGeoRouteReply::QGeoRouteReply(Error error, const QString &errorString, QObject *parent)
    : QObject(parent),
      d_ptr(new QGeoRouteReplyPrivate(error, errorString)) {}

/*!
    Destroys this route reply object.
*/
QGeoRouteReply::~QGeoRouteReply()
{
    delete d_ptr;
}

/*!
    Sets whether or not this reply has finished to \a finished.

    If \a finished is true, this will cause the finished() signal to be
    emitted.

    If the operation completed successfully, QGeoRouteReply::setRoutes() should
    be called before this function. If an error occured,
    QGeoRouteReply::setError() should be used instead.
*/
void QGeoRouteReply::setFinished(bool finished)
{
    d_ptr->isFinished = finished;
    if (d_ptr->isFinished)
        emit this->finished();
}

/*!
    Return true if the operation completed successfully or encountered an
    error which cause the operation to come to a halt.
*/
bool QGeoRouteReply::isFinished() const
{
    return d_ptr->isFinished;
}

/*!
    Sets the error state of this reply to \a error and the textual
    representation of the error to \a errorString.

    This wil also cause error() and finished() signals to be emitted, in that
    order.
*/
void QGeoRouteReply::setError(QGeoRouteReply::Error error, const QString &errorString)
{
    d_ptr->error = error;
    d_ptr->errorString = errorString;
    emit this->error(error, errorString);
    setFinished(true);
}

/*!
    Returns the error state of this reply.

    If the result is QGeoRouteReply::NoError then no error has occurred.
*/
QGeoRouteReply::Error QGeoRouteReply::error() const
{
    return d_ptr->error;
}

/*!
    Returns the textual representation of the error state of this reply.

    If no error has occurred this will return an empty string.  It is possible
    that an error occurred which has no associated textual representation, in
    which case this will also return an empty string.

    To determine whether an error has occurred, check to see if
    QGeoRouteReply::error() is equal to QGeoRouteReply::NoError.
*/
QString QGeoRouteReply::errorString() const
{
    return d_ptr->errorString;
}

/*!
    Returns the route request which specified the route.
*/
QGeoRouteRequest QGeoRouteReply::request() const
{
    return d_ptr->request;
}

/*!
    Returns the list of routes which were requested.
*/
QList<QGeoRoute> QGeoRouteReply::routes() const
{
    return d_ptr->routes;
}

/*!
    Sets the list of routes in the reply to \a routes.
*/
void QGeoRouteReply::setRoutes(const QList<QGeoRoute> &routes)
{
    d_ptr->routes = routes;
}

/*!
    Cancels the operation immediately.

    This will do nothing if the reply is finished.
*/
void QGeoRouteReply::abort()
{
    if (!isFinished())
        setFinished(true);
}

/*!
    \fn void QGeoRouteReply::finished()

    This signal is emitted when this reply has finished processing.

    If error() equals QGeoRouteReply::NoError then the processing
    finished successfully.

    This signal and QGeoRoutingManager::finished() will be
    emitted at the same time.

    \note Do no delete this reply object in the slot connected to this
    signal. Use deleteLater() instead.
*/
/*!
    \fn void QGeoRouteReply::error(QGeoRouteReply::Error error, const QString &errorString)

    This signal is emitted when an error has been detected in the processing of
    this reply. The finished() signal will probably follow.

    The error will be described by the error code \a error. If \a errorString is
    not empty it will contain a textual description of the error.

    This signal and QGeoRoutingManager::error() will be emitted at the same time.

    \note Do no delete this reply object in the slot connected to this
    signal. Use deleteLater() instead.
*/

/*******************************************************************************
*******************************************************************************/

QGeoRouteReplyPrivate::QGeoRouteReplyPrivate(const QGeoRouteRequest &request)
    : error(QGeoRouteReply::NoError),
      errorString(""),
      isFinished(false),
      request(request) {}

QGeoRouteReplyPrivate::QGeoRouteReplyPrivate(QGeoRouteReply::Error error, QString errorString)
    : error(error),
      errorString(errorString),
      isFinished(true) {}

QGeoRouteReplyPrivate::~QGeoRouteReplyPrivate() {}

#include "moc_qgeoroutereply.cpp"

QTM_END_NAMESPACE
