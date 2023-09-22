#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#pragma once

#include "../ir_gui_remotes.h"

typedef struct App App;

// List of Main Menu Scenes
typedef enum {
    IrGuiRemotesMainMenuSceneLedStripe,
    IrGuiRemotesMainMenuSceneLedSign,
} IrGuiRemotesMainMenuSceneIndex;

// Event for Main Menu Scenes
typedef enum {
    IrGuiRemotesMainMenuSceneLedStripeEvent,
    IrGuiRemotesMainMenuSceneLedSignEvent,
} IrGuiRemotesMainMenuSceneEvent;

/**
 * Main Menu Handlers
 * 
 * @param context App context
 * @param index Index of the selected item
 * 
 * @return void
*/
void main_menu_scene_callback(void* context, uint32_t index);

/**
 * Setup and draw the Main Menu
 * 
 * @param context App context
 * 
 * @return void
*/
void main_menu_scene_on_enter(void* context);

/**
 * Handle Events inside Main Menu
 * 
 * @param context App context
 * @param event Event to handle
 * 
 * @return bool True if event was consumed, false otherwise
*/
bool main_menu_scene_on_event(void* context, SceneManagerEvent event);

/**
 * Cleanup Main Menu on Exit
 * 
 * @param context App context
 * 
 * @return void
*/
void main_menu_scene_on_exit(void* context);

#endif // MAIN_MENU_SCENE_H
