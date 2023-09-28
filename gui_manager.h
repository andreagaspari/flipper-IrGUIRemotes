#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#pragma once

#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/submenu.h>
#include <gui/modules/dialog_ex.h>

#include "views/led_remote_view.h"
#include "views/infrared_gui_remote_view.h"

#include "scenes/main_menu_scene.h"
#include "scenes/led_stripe_scene.h"
#include "scenes/led_sign_scene.h"
#include "scenes/infrared_remote_list_scene.h"
#include "scenes/infrared_remote_scene.h"

#include "ir_gui_remotes.h"

typedef struct App App;

// List of Scenes
typedef enum {
    IrGuiRemotesMainMenuScene,
    IrGuiRemotesLedStripeScene,
    IrGuiRemotesLedSignScene,
    IrGuiRemotesInfraredRemoteListScene,
    IrGuiRemotesInfraredRemoteScene,
    IrGuiRemotesSceneCount
} IrGuiRemotesScene;

// List of Views
typedef enum { 
    IrGuiRemotesMainMenuView,
    IrGuiRemotesLedRemoteView,
    IrGuiRemotesInfraredGuiRemoteView
} IrGuiRemotesView;

/**
 * GUIManager structure
 * 
 * @param app App data
 * @param scene_manager Scene Manager
 * @param view_dispatcher View Dispatcher
 * @param led_remote_view Led Remote View
 * @param infrared_gui_remote_view Infrared GUI Remote View
 * @param submenu Submenu
 * 
*/
typedef struct GUIManager {
    App* app;

    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;

    LedRemoteView* led_remote_view;
    InfraredGuiRemoteView* infrared_gui_remote_view;
    Submenu* submenu;

    DialogEx* dialog_ex;
} GUIManager;

/**
 * Scene Manager Allocation
 * 
 * @param app App data
 * 
 * @return SceneManager* Scene Manager
*/
SceneManager* ir_gui_remotes_scene_manager_alloc(App* app);

/**
 * Custom Event Callback
 * 
 * @param context Context
 * @param custom_event Custom Event
 * 
 * @return bool True if event was handled
*/
bool scene_custom_callback(void* context, uint32_t custom_event);

/**
 * Back Event Callback
 * 
 * @param context Context
 * 
 * @return bool True if event was handled
*/
bool back_event_callback(void* context);

/**
 * GUI Manager Allocation
 * 
 * @param app App data
 * 
 * @return GUIManager* GUI Manager
*/
GUIManager* gui_manager_alloc(App* app);

/**
 * Run GUI Manager -> show first scene
 * 
 * @param gui_manager GUI Manager
 * 
 * @return void
*/
void gui_manager_run(GUIManager* gui_manager);

/**
 * GUI Manager Free
 * 
 * @param gui_manager GUI Manager
 * 
 * @return void
*/
void gui_manager_free(GUIManager* gui_manager);

#endif // GUI_MANAGER_H