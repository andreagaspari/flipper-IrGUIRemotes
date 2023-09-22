#ifndef LED_SIGN_SCENE_H
#define LED_SIGN_SCENE_H

#pragma once
#include "../ir_gui_remotes.h"

/**
 * Led Sign scene setup
 * 
 * @param context App context
 * 
 * @return void
*/
void led_sign_scene_on_enter(void* context);

/**
 * Led Sign scene event handler
 * 
 * @param context App context
 * @param event Event to handle
 * 
 * @return bool True if event was consumed, false otherwise
*/
bool led_sign_scene_on_event(void* context, SceneManagerEvent event);

/**
 * Cleanup Led Sign scene on Exit
 * 
 * @param context App context
 * 
 * @return void
*/
void led_sign_scene_on_exit(void* context);

#endif // LED_SIGN_SCENE_H