/*
 * Copyright (C) 2018 Michał Siejak
 * This file is part of Quartz - a raytracing aspect for Qt3D.
 * See LICENSE file for licensing information.
 */

#pragma once

#include <Qt3DRaytrace/qt3draytrace_global.h>
#include <Qt3DRaytrace/qimagedata.h>
#include <Qt3DRaytrace/qrenderimage.h>

#include <Qt3DCore/qabstractaspect.h>

class QSurface;

namespace Qt3DRaytrace {

class QRaytraceAspectPrivate;

class QT3DRAYTRACESHARED_EXPORT QRaytraceAspect : public Qt3DCore::QAbstractAspect
{
    Q_OBJECT
public:
    explicit QRaytraceAspect(QObject *parent = nullptr);

    QSurface *surface() const;
    void setSurface(QObject *surfaceObject);

    bool queryRenderStatistics(QRenderStatistics &statistics) const;

public slots:
    void suspendJobs();
    void resumeJobs();
    void requestImage(Qt3DRaytrace::QRenderImage type);

signals:
    void imageReady(Qt3DRaytrace::QRenderImage type, Qt3DRaytrace::QImageDataPtr image);

protected:
    QRaytraceAspect(QRaytraceAspectPrivate &dd, QObject *parent);
    Q_DECLARE_PRIVATE(QRaytraceAspect)

private:
    Q_INVOKABLE void grabImage(Qt3DRaytrace::QRenderImage type);

    QVector<Qt3DCore::QAspectJobPtr> jobsToExecute(qint64 time) override;

    void onRegistered() override;
    void onUnregistered() override;
    void onEngineStartup() override;
    void onEngineShutdown() override;
};

} // Qt3DRaytrace
