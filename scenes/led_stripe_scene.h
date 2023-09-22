#ifndef LED_STRIPE_SCENE_H
#define LED_STRIPE_SCENE_H

#pragma once
#include "../ir_gui_remotes.h"

/**
 * Led Stripe scene setup
 * 
 * @param context App context
 * 
 * @return void
*/
void led_stripe_scene_on_enter(void* context);

/**
 * Led Stripe scene event handler
 * 
 * @param context App context
 * @param event Event to handle
 * 
 * @return bool True if event was consumed, false otherwise
*/
bool led_stripe_scene_on_event(void* context, SceneManagerEvent event);

/**
 * Cleanup Led Stripe scene on Exit
 * 
 * @param context App context
 * 
 * @return void
*/
void led_stripe_scene_on_exit(void* context);

#endif // LED_STRIPE_SCENE_H