#include "led_sign_scene.h"
#include "../remotes/led_sign.h"

/**
 * Led Sign scene setup
 * 
 * @param context App context
 * 
 * @return void
*/
void led_sign_scene_on_enter(void* context) {
    App* app = context;

    // Get Model and set Led Sign Remote
    LedRemoteModel* remote_model = view_get_model(app->gui_manager->led_remote_view->view);
    remote_model->remote = &led_sign_remote;
    remote_model->selected_btn = 0;

    // Commit Model
    view_commit_model(app->gui_manager->led_remote_view->view, false);

    // Switch to Led Remote View
    view_dispatcher_switch_to_view(app->gui_manager->view_dispatcher, IrGuiRemotesLedRemoteView);
}

/**
 * Led Sign scene event handler
 * 
 * @param context App context
 * @param event Event to handle
 * 
 * @return bool True if event was consumed, false otherwise
*/
bool led_sign_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);

    return false;
}

/**
 * Cleanup Led Sign scene on Exit
 * 
 * @param context App context
 * 
 * @return void
*/
void led_sign_scene_on_exit(void* context) {
    UNUSED(context);
}