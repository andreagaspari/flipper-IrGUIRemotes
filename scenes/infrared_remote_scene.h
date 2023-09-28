#ifndef INFRARED_REMOTE_SCENE_H
#define INFRARED_REMOTE_SCENE_H

#pragma once
#include "../ir_gui_remotes.h"

/**
 * Infrared remote scene setup
 * 
 * @param context App context
 * 
 * @return void
*/
void infrared_remote_scene_on_enter(void* context);

/**
 * Led Sign scene event handler
 * 
 * @param context App context
 * @param event Event to handle
 * 
 * @return bool True if event was consumed, false otherwise
*/
bool infrared_remote_scene_on_event(void* context, SceneManagerEvent event);

/**
 * Cleanup Led Sign scene on Exit
 * 
 * @param context App context
 * 
 * @return void
*/
void infrared_remote_scene_on_exit(void* context);

#endif // INFRARED_REMOTE_SCENE_H