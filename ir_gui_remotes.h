#ifndef IR_GUI_REMOTES_H
#define IR_GUI_REMOTES_H

#pragma once

#include <furi.h>

#include <dialogs/dialogs.h>
#include <storage/storage.h>

#include <infrared/worker/infrared_worker.h>

#include <notification/notification_messages.h>

#include "gui_manager.h"
#include "ir_gui_remotes_icons.h"

typedef struct App App;
typedef struct GUIManager GUIManager;

typedef struct InfraredGuiRemoteButton InfraredGuiRemoteButton;
typedef struct InfraredGuiRemote InfraredGuiRemote;

/**
 * Infrared Gui Remote Button Data Structure
 * 
 * @param label Button Label
 * @param ir_message Infrared Message
 * @param icon Icon
 * @param icon_hover Icon Hover
*/
struct InfraredGuiRemoteButton {
    const char* label;
    const InfraredMessage ir_message;
    const Icon* icon;
    const Icon* icon_hover;
    const int color;
};

/**
 * Infrared Gui Remote Data Structure
 * 
 * @param label Label
 * @param rows Rows
 * @param cols Columns
 * @param buttons Buttons
 * 
*/
struct InfraredGuiRemote {
    char* label;
    InfraredGuiRemoteButton* buttons;
};


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

    DialogsApp* dialogs;
    Storage* storage;
    FuriString* file_path;

    // Infrared Worker
    InfraredWorker* ir_worker;
    bool ir_transmitting;

    // Remote
    InfraredGuiRemote* remote;
    
    // Notifications
    NotificationApp* notifications;
};

/**
 * Turn on Notification LED with Hex color code
 * 
 * @param context App context
 * @param hexColor Hex Color
 * 
 * @return void
*/
void turn_on_led(void* context, int hexColor);

/**
 * Turn off Notification LED
 * 
 * @param context App context
 * 
 * @return void
*/
void turn_off_led(void* context);

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