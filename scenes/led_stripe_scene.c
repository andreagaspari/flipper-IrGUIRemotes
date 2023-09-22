#include "led_stripe_scene.h"
#include "../remotes/led_stripe.h"

/**
 * Led Stripe scene setup
 * 
 * @param context App context
 * 
 * @return void
*/
void led_stripe_scene_on_enter(void* context) {
    App* app = context;

    // Set Led Stripe Remote on Model
    LedRemoteModel* remote_model = view_get_model(app->gui_manager->led_remote_view->view);
    remote_model->remote = &led_stripe_remote;
    remote_model->selected_btn = 0;
    view_commit_model(app->gui_manager->led_remote_view->view, false);

    // Switch to Led Remote View
    view_dispatcher_switch_to_view(app->gui_manager->view_dispatcher, IrGuiRemotesLedRemoteView);
}

/**
 * Led Stripe scene event handler
 * 
 * @param context App context
 * @param event Event to handle
 * 
 * @return bool True if event was consumed, false otherwise
*/
bool led_stripe_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);

    return false;
}

/**
 * Cleanup Led Stripe scene on Exit
 * 
 * @param context App context
 * 
 * @return void
*/
void led_stripe_scene_on_exit(void* context) {
    UNUSED(context);
}