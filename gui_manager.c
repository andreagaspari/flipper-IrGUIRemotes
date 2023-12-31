#include "gui_manager.h"

// OnEnter Scene Handlers
void (*const scene_on_enter_handlers[])(void*) = {
    main_menu_scene_on_enter,
    led_stripe_scene_on_enter,
    led_sign_scene_on_enter,
    infrared_remote_list_scene_on_enter,
    infrared_remote_scene_on_enter    
};

// OnEvent Scene Handlers
bool (*const scene_on_event_handlers[])(void*, SceneManagerEvent) = {
    main_menu_scene_on_event,
    led_stripe_scene_on_event,
    led_sign_scene_on_event,
    infrared_remote_list_scene_on_event,
    infrared_remote_scene_on_event
};

// OnExit Scene Handlers
void (*const scene_on_exit_handlers[])(void*) = {
    main_menu_scene_on_exit,
    led_stripe_scene_on_exit,
    led_sign_scene_on_exit,
    infrared_remote_list_scene_on_exit,
    infrared_remote_scene_on_exit
};

// Scene Manager Handlers
static const SceneManagerHandlers scene_manager_handlers = {
    .on_enter_handlers = scene_on_enter_handlers,
    .on_event_handlers = scene_on_event_handlers,
    .on_exit_handlers = scene_on_exit_handlers,
    .scene_num = IrGuiRemotesSceneCount,
};

/**
 * Scene Manager Allocation
 * 
 * @param app App data
 * 
 * @return SceneManager* Scene Manager
*/
SceneManager* ir_gui_remotes_scene_manager_alloc(App* app) {
    return scene_manager_alloc(&scene_manager_handlers, app);
}

/**
 * Custom Event Callback
 * 
 * @param context Context
 * @param custom_event Custom Event
 * 
 * @return bool True if event was handled
*/
bool scene_custom_callback(void* context, uint32_t custom_event) {
    furi_assert(context);
    App* app = context;

    // Handle custom event
    return scene_manager_handle_custom_event(app->gui_manager->scene_manager, custom_event);
}

/**
 * Back Event Callback
 * 
 * @param context Context
 * 
 * @return bool True if event was handled
*/
bool back_event_callback(void* context) {
    furi_assert(context);
    App* app = context;

    // Turn off Led
    turn_off_led(app);

    // Handle back event
    return scene_manager_handle_back_event(app->gui_manager->scene_manager);
}

/**
 * GUI Manager Allocation
 * 
 * @param app App data
 * 
 * @return GUIManager* GUI Manager
*/
GUIManager* gui_manager_alloc(App* app) {
    // Allocate GUI Manager
    GUIManager* gui_manager = malloc(sizeof(GUIManager));

    // Set App
    gui_manager->app = app;

    // Allocate UI handlers
    gui_manager->scene_manager = scene_manager_alloc(&scene_manager_handlers, app);
    gui_manager->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(gui_manager->view_dispatcher);
    view_dispatcher_set_event_callback_context(gui_manager->view_dispatcher, app);
    view_dispatcher_set_custom_event_callback(gui_manager->view_dispatcher, scene_custom_callback);
    view_dispatcher_set_navigation_event_callback(gui_manager->view_dispatcher, back_event_callback);

    // Allocate Submenu and add it to the View Dispatcher
    gui_manager->submenu = submenu_alloc();
    view_dispatcher_add_view(gui_manager->view_dispatcher, IrGuiRemotesMainMenuView, submenu_get_view(gui_manager->submenu));

    //  Allocate Led Remote View
    gui_manager->led_remote_view = led_remote_view_alloc(app);
    // Add Led Remote View to the View Dispatcher
    view_dispatcher_add_view(gui_manager->view_dispatcher, IrGuiRemotesLedRemoteView, gui_manager->led_remote_view->view);

    // Allocate Infrared Gui Remote View
    gui_manager->infrared_gui_remote_view = infrared_gui_remote_view_alloc(app);
    // Add Infrared Gui Remote View to the View Dispatcher
    view_dispatcher_add_view(gui_manager->view_dispatcher, IrGuiRemotesInfraredGuiRemoteView, gui_manager->infrared_gui_remote_view->view);

    return gui_manager;
}

/**
 * Run GUI Manager -> show first scene
 * 
 * @param gui_manager GUI Manager
 * 
 * @return void
*/
void gui_manager_run(GUIManager* gui_manager) {
    // Initialize GUI
    Gui* gui = furi_record_open(RECORD_GUI);

    // Attach View Dispatcher to GUI
    view_dispatcher_attach_to_gui(gui_manager->view_dispatcher, gui, ViewDispatcherTypeFullscreen);
    // Switch to Main Menu Scene
    scene_manager_next_scene(gui_manager->scene_manager, IrGuiRemotesMainMenuView);
    // Run View Dispatcher
    view_dispatcher_run(gui_manager->view_dispatcher);
}

/**
 * GUI Manager Free
 * 
 * @param gui_manager GUI Manager
 * 
 * @return void
*/
void gui_manager_free(GUIManager* gui_manager) {
    // Debug GUI Manager Check
    furi_assert(gui_manager);

    // Remove Views from View Dispatcher
    view_dispatcher_remove_view(gui_manager->view_dispatcher, IrGuiRemotesMainMenuView);
    view_dispatcher_remove_view(gui_manager->view_dispatcher, IrGuiRemotesLedRemoteView);

    // Free UI handlers
    scene_manager_free(gui_manager->scene_manager);
    view_dispatcher_free(gui_manager->view_dispatcher);
    submenu_free(gui_manager->submenu);

    // Free Led Remote View
    led_remote_view_free(gui_manager->led_remote_view);

    // Free Infrared Gui Remote View
    infrared_gui_remote_view_free(gui_manager->infrared_gui_remote_view);

    // Free GUI Manager
    free(gui_manager);
}
