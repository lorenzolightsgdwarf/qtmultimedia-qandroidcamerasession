/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGSTREAMERVIDEOWINDOW_H
#define QGSTREAMERVIDEOWINDOW_H

#include <qvideowindowcontrol.h>

#include "qgstreamervideorendererinterface_p.h"
#include <private/qgstreamerbushelper_p.h>
#include <QtGui/qcolor.h>

QT_BEGIN_NAMESPACE
class QAbstractVideoSurface;
class QX11VideoSurface;

class QGstreamerVideoWindow : public QVideoWindowControl,
        public QGstreamerVideoRendererInterface,
        public QGstreamerSyncMessageFilter
{
    Q_OBJECT
    Q_INTERFACES(QGstreamerVideoRendererInterface QGstreamerSyncMessageFilter)
    Q_PROPERTY(QColor colorKey READ colorKey WRITE setColorKey)
    Q_PROPERTY(bool autopaintColorKey READ autopaintColorKey WRITE setAutopaintColorKey)
public:
    QGstreamerVideoWindow(QObject *parent = 0, const char *elementName = 0);
    ~QGstreamerVideoWindow();

    WId winId() const;
    void setWinId(WId id);

    QRect displayRect() const;
    void setDisplayRect(const QRect &rect);

    bool isFullScreen() const;
    void setFullScreen(bool fullScreen);

    QSize nativeSize() const;

    Qt::AspectRatioMode aspectRatioMode() const;
    void setAspectRatioMode(Qt::AspectRatioMode mode);

    QColor colorKey() const;
    void setColorKey(const QColor &);

    bool autopaintColorKey() const;
    void setAutopaintColorKey(bool);

    void repaint();

    int brightness() const;
    void setBrightness(int brightness);

    int contrast() const;
    void setContrast(int contrast);

    int hue() const;
    void setHue(int hue);

    int saturation() const;
    void setSaturation(int saturation);

    QAbstractVideoSurface *surface() const;

    GstElement *videoSink();

    bool processSyncMessage(const QGstreamerMessage &message);
    bool isReady() const { return m_windowId != 0; }

signals:
    void sinkChanged();
    void readyChanged(bool);

private slots:
    void updateNativeVideoSize();

private:
    static void padBufferProbe(GstPad *pad, GstBuffer *buffer, gpointer user_data);

    GstElement *m_videoSink;
    WId m_windowId;
    Qt::AspectRatioMode m_aspectRatioMode;
    QRect m_displayRect;
    bool m_fullScreen;
    QSize m_nativeSize;
    mutable QColor m_colorKey;
    int m_bufferProbeId;
};

QT_END_NAMESPACE

#endif
