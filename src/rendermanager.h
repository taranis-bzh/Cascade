/*
 *  Cascade Image Editor
 *
 *  Copyright (C) 2020 The Cascade developers
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <QObject>

#include "nodebase.h"
#include "nodedefinitions.h"

class VulkanRenderer;
class NodeGraph;

class RenderManager : public QObject
{
    Q_OBJECT

public:
    static RenderManager& getInstance();
    RenderManager(RenderManager const&) = delete;
    void operator=(RenderManager const&) = delete;

    void setUp(VulkanRenderer* r, NodeGraph* ng);

    void updateViewerPushConstants(const QString& s);

private:
    RenderManager() {}
    void displayNode(NodeBase* node);
    bool renderNodes(NodeBase* node);
    void renderNode(NodeBase* node);

    VulkanRenderer* renderer;
    NodeGraph* nodeGraph;

    WindowManager* wManager;

public slots:
    void handleNodeDisplayRequest(NodeBase* node);
    void handleNodeFileSaveRequest(NodeBase* node, const QString& path);
    void handleClearScreenRequest();
};

#endif // RENDERMANAGER_H
