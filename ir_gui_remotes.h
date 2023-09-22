#ifndef IR_GUI_REMOTES_H
#define IR_GUI_REMOTES_H

#pragma once

#include <furi.h>

#include <infrared/worker/infrared_worker.h>

#include "gui_manager.h"

#include "ir_gui_remotes_icons.h"

typedef struct App App;
typedef struct GUIManager GUIManager;

struct App {
    // GUI Manager
    GUIManager* gui_manager;

    // Infrared
    InfraredWorker* ir_worker;
    bool ir_transmitting;
};

void start_ir_transmission(InfraredMessage* ir_message, void* context);
void stop_ir_transmission(void* context);

#endif // IR_GUI_REMOTES_H