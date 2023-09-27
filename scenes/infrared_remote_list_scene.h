#ifndef INFRARED_REMOTE_LIST_SCENE_H
#define INFRARED_REMOTE_LIST_SCENE_H

#pragma once
#include "../ir_gui_remotes.h"

#define INFRARED_APP_FOLDER ANY_PATH("infrared")
#define INFRARED_APP_EXTENSION ".igr"

#define INFRARED_DEFAULT_REMOTE_NAME "Remote"

/**
 * Infrared remote list scene setup
 * 
 * @param context App context
 * 
 * @return void
*/
void infrared_remote_list_scene_on_enter(void* context);

/**
 * Led Sign scene event handler
 * 
 * @param context App context
 * @param event Event to handle
 * 
 * @return bool True if event was consumed, false otherwise
*/
bool infrared_remote_list_scene_on_event(void* context, SceneManagerEvent event);

/**
 * Cleanup Led Sign scene on Exit
 * 
 * @param context App context
 * 
 * @return void
*/
void infrared_remote_list_scene_on_exit(void* context);

#endif // INFRARED_REMOTE_LIST_SCENE_H