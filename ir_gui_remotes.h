#ifndef IR_GUI_REMOTES_H
#define IR_GUI_REMOTES_H

#pragma once

#include <furi.h>
#include <infrared/worker/infrared_worker.h>

#include "gui_manager.h"
#include "ir_gui_remotes_icons.h"

typedef struct App App;
typedef struct GUIManager GUIManager;

/**
 * App Structure Definition
 * 
 * @param gui_manager GUI Manager
 * @param ir_worker Infrared Worker
 * @param ir_transmitting Infrared Transmitting Flag
 * 
 */
struct App {
    // GUI Manager
    GUIManager* gui_manager;

    // Infrared
    InfraredWorker* ir_worker;
    bool ir_transmitting;
};

/**
 * Start transmitting Infrared Message
 * 
 * @param ir_message Infrared Message to transmit
 * 
 * @return void
*/
void start_ir_transmission(InfraredMessage* ir_message, void* context);

/**
 * Stop transmitting Infrared Message
 * 
 * @param context App context
 * 
 * @return void
*/
void stop_ir_transmission(void* context);

#endif // IR_GUI_REMOTES_H