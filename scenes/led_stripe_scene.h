#ifndef LED_STRIPE_SCENE_H
#define LED_STRIPE_SCENE_H

#pragma once
#include "../ir_gui_remotes.h"

void led_stripe_scene_on_enter(void* context);
bool led_stripe_scene_on_event(void* context, SceneManagerEvent event);
void led_stripe_scene_on_exit(void* context);

#endif // LED_STRIPE_SCENE_H