#include "ir_gui_remotes.h"

/**
 * Start transmitting Infrared Message
 * 
 * @param ir_message Infrared Message to transmit
 * @param context App context
 * 
 * @return void
*/
void start_ir_transmission(InfraredMessage* ir_message, void* context) {
    App* app = context;

    // If already transmitting, stop
    if(!app->ir_transmitting) {
        infrared_worker_set_decoded_signal(app->ir_worker, ir_message);
        infrared_worker_tx_set_get_signal_callback(
            app->ir_worker, infrared_worker_tx_get_signal_steady_callback, app);
        infrared_worker_tx_start(app->ir_worker);
        app->ir_transmitting = true;
    }
}

/**
 * Stop transmitting Infrared Message
 * 
 * @param context App context
 * 
 * @return void
*/
void stop_ir_transmission(void* context) {
    App* app = context;

    if(app->ir_transmitting) {
        infrared_worker_tx_stop(app->ir_worker);
        infrared_worker_tx_set_get_signal_callback(app->ir_worker, NULL, NULL);
        app->ir_transmitting = false;
    }
}

// List of Scene Handlers on Enter
void (*const scene_on_enter_handlers[])(void*) = {
    main_menu_scene_on_enter,
    led_stripe_scene_on_enter,
    led_sign_scene_on_enter,
};
// List of Scene Handlers on Event
bool (*const scene_on_event_handlers[])(void*, SceneManagerEvent) = {
    main_menu_scene_on_event,
    led_stripe_scene_on_event,
    led_sign_scene_on_event,
};
// List of Scene Handlers on Exit
void (*const scene_on_exit_handlers[])(void*) = {
    main_menu_scene_on_exit,
    led_stripe_scene_on_exit,
    led_sign_scene_on_exit,
};

// Scene Manager Handlers
static const SceneManagerHandlers scene_manager_handlers = {
    .on_enter_handlers = scene_on_enter_handlers,
    .on_event_handlers = scene_on_event_handlers,
    .on_exit_handlers = scene_on_exit_handlers,
    .scene_num = IrGuiRemotesSceneCount,
};

// Custom Event Callback
static bool scene_custom_callback(void* context, uint32_t custom_event) {
    furi_assert(context);
    App* app = context;

    // Handle custom event
    return scene_manager_handle_custom_event(app->scene_manager, custom_event);
}

// Back Event Callback
bool back_event_callback(void* context) {
    furi_assert(context);
    App* app = context;

    // Handle back event
    return scene_manager_handle_back_event(app->scene_manager);
}

/**
 * App Data Allocation
 * 
 * @return App* App data
*/
static App* app_alloc() {
    // Allocate App
    App* app = malloc(sizeof(App));

    // Allocate Infrared Worker and transmit flag
    app->ir_worker = infrared_worker_alloc();
    app->ir_transmitting = false;

    // Allocate UI handlers
    app->scene_manager = scene_manager_alloc(&scene_manager_handlers, app);
    app->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(app->view_dispatcher);
    view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
    view_dispatcher_set_custom_event_callback(app->view_dispatcher, scene_custom_callback);
    view_dispatcher_set_navigation_event_callback(app->view_dispatcher, back_event_callback);

    // Allocate Submenu and add it to the View Dispatcher
    app->submenu = submenu_alloc();
    view_dispatcher_add_view(
        app->view_dispatcher, IrGuiRemotesMainMenuView, submenu_get_view(app->submenu));

    //  Allocate Led Remote View
    app->led_remote_view = led_remote_view_alloc(app);

    // Add Led Remote View to the View Dispatcher
    view_dispatcher_add_view(
        app->view_dispatcher, IrGuiRemotesLedRemoteView, app->led_remote_view->view);

    return app;
}

/**
 * App Data Free
 * 
 * @param app App data
 * 
 * @return void
*/
static void app_free(App* app) {
    // Debug App Check
    furi_assert(app);

    // Free Infrared Worker
    infrared_worker_free(app->ir_worker);

    // Remove Views from View Dispatcher
    view_dispatcher_remove_view(app->view_dispatcher, IrGuiRemotesMainMenuView);
    view_dispatcher_remove_view(app->view_dispatcher, IrGuiRemotesLedRemoteView);

    // Free UI handlers
    scene_manager_free(app->scene_manager);
    view_dispatcher_free(app->view_dispatcher);
    submenu_free(app->submenu);

    // Free Led Remote View
    led_remote_view_free(app);

    // Free App
    free(app);
}

/**
 * Led Remotes App - Entry Point
 * 
 * @param p Unused
 * 
 * @return int32_t Unused
*/
int32_t ir_gui_remotes_app(void* p) {
    // Unused params
    UNUSED(p);
    // Allocate App
    App* app = app_alloc();
    // Initialize GUI
    Gui* gui = furi_record_open(RECORD_GUI);

    // Attach View Dispatcher to GUI
    view_dispatcher_attach_to_gui(app->view_dispatcher, gui, ViewDispatcherTypeFullscreen);
    // Switch to Main Menu Scene
    scene_manager_next_scene(app->scene_manager, IrGuiRemotesMainMenuView);
    // Run View Dispatcher
    view_dispatcher_run(app->view_dispatcher);

    // Free App on exit
    app_free(app);
    return 0;
}