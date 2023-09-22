#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#pragma once

#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/submenu.h>

#include "views/led_remote_view.h"

#include "scenes/main_menu_scene.h"
#include "scenes/led_stripe_scene.h"
#include "scenes/led_sign_scene.h"

#include "ir_gui_remotes.h"

typedef struct App App;

// List Scenes
typedef enum {
    IrGuiRemotesMainMenuScene,
    IrGuiRemotesLedStripeScene,
    IrGuiRemotesLedSignScene,
    IrGuiRemotesSceneCount
} IrGuiRemotesScene;

// List of Views
typedef enum { IrGuiRemotesMainMenuView, IrGuiRemotesLedRemoteView } IrGuiRemotesView;

typedef struct GUIManager {
    App* app;

    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;

    LedRemoteView* led_remote_view;
    Submenu* submenu;
} GUIManager;

SceneManager* ir_gui_remotes_scene_manager_alloc(App* app);

bool scene_custom_callback(void* context, uint32_t custom_event);
bool back_event_callback(void* context);

GUIManager* gui_manager_alloc(App* app);
void gui_manager_run(GUIManager* gui_manager);
void gui_manager_free(GUIManager* gui_manager);

#endif // GUI_MANAGER_H