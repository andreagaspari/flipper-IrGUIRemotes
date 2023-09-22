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

void main_menu_scene_callback(void* context, uint32_t index);
void main_menu_scene_on_enter(void* context);
bool main_menu_scene_on_event(void* context, SceneManagerEvent event);
void main_menu_scene_on_exit(void* context);

#endif // MAIN_MENU_SCENE_H
