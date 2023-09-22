#ifndef LED_SIGN_SCENE_H
#define LED_SIGN_SCENE_H

#pragma once
#include "../ir_gui_remotes.h"

void led_sign_scene_on_enter(void* context);
bool led_sign_scene_on_event(void* context, SceneManagerEvent event);
void led_sign_scene_on_exit(void* context);

#endif // LED_SIGN_SCENE_H