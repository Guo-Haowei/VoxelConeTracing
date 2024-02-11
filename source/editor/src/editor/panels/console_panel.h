#pragma once
#include "panel.h"

class ConsolePanel : public Panel {
public:
    ConsolePanel() : Panel("Console") {}

protected:
    void RenderInternal(Scene& scene) override;

private:
    bool mAutoScroll = true;
    bool mScrollToBottom = false;
};
