#include "vulkanwindow.h"

#include <iostream>

#include <QMouseEvent>

#include "vulkanrenderer.h"

QVulkanWindowRenderer *VulkanWindow::createRenderer()
{
    qDebug("Creating renderer");

    renderer = new VulkanRenderer(this);

    return renderer;
}

VulkanRenderer* VulkanWindow::getRenderer()
{
    return renderer;
}

void VulkanWindow::handleZoomResetRequest()
{
    scale = 1.0;
    renderer->scale(1.0);
}

ViewerMode VulkanWindow::getViewerMode()
{
    return viewerMode;
}

void VulkanWindow::setViewerMode(const ViewerMode mode)
{
    viewerMode = mode;
}

void VulkanWindow::mousePressEvent(QMouseEvent *e)
{
    pressed = true;
    lastPos = e->pos();
}

void VulkanWindow::mouseReleaseEvent(QMouseEvent *)
{
    pressed = false;
}

void VulkanWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (!pressed)
        return;

    float dx        = e->pos().x() - lastPos.x();
    float dy        = e->pos().y() - lastPos.y();
    float magnitude = std::max(abs(dx),abs(dy));

    if (  magnitude > 0.0f )
    {
        renderer->translate(dx, dy);
    }
    lastPos = e->pos();
}

void VulkanWindow::wheelEvent(QWheelEvent *e)
{
    e->angleDelta().y() > 0 ? scale += scale * 0.1f : scale -= scale * 0.1f;

    //Limit the scale
    scale = scale > minScale ? scale : minScale;
    scale = scale < maxScale ? scale : maxScale;
    renderer->scale(scale);
}

