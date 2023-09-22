#ifndef IR_GUI_REMOTES_H
#define IR_GUI_REMOTES_H

#pragma once

#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/submenu.h>

#include <infrared/worker/infrared_worker.h>

#include "views/led_remote_view.h"

#include "scenes/main_menu_scene.h"
#include "scenes/led_stripe_scene.h"
#include "scenes/led_sign_scene.h"

#include "ir_gui_remotes_icons.h"

typedef struct App App;

struct App {
    // UI Handlers
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;

    // Led Remote View
    LedRemoteView* led_remote_view;

    // Submenu
    Submenu* submenu;

    // Infrared
    InfraredWorker* ir_worker;
    bool ir_transmitting;
};

// List Scenes
typedef enum {
    IrGuiRemotesMainMenuScene,
    IrGuiRemotesLedStripeScene,
    IrGuiRemotesLedSignScene,
    IrGuiRemotesSceneCount
} IrGuiRemotesScene;

// List Views
typedef enum { IrGuiRemotesMainMenuView, IrGuiRemotesLedRemoteView } IrGuiRemotesView;

void start_ir_transmission(InfraredMessage* ir_message, void* context);
void stop_ir_transmission(void* context);

#endif // IR_GUI_REMOTES_H