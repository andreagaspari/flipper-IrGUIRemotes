#include "gui_manager.h"

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

SceneManager* ir_gui_remotes_scene_manager_alloc(App* app) {
    return scene_manager_alloc(&scene_manager_handlers, app);
}

// Custom Event Callback
bool scene_custom_callback(void* context, uint32_t custom_event) {
    furi_assert(context);
    App* app = context;

    // Handle custom event
    return scene_manager_handle_custom_event(app->gui_manager->scene_manager, custom_event);
}

// Back Event Callback
bool back_event_callback(void* context) {
    furi_assert(context);
    App* app = context;

    // Handle back event
    return scene_manager_handle_back_event(app->gui_manager->scene_manager);
}

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
    view_dispatcher_set_navigation_event_callback(
        gui_manager->view_dispatcher, back_event_callback);

    // Allocate Submenu and add it to the View Dispatcher
    gui_manager->submenu = submenu_alloc();
    view_dispatcher_add_view(
        gui_manager->view_dispatcher,
        IrGuiRemotesMainMenuView,
        submenu_get_view(gui_manager->submenu));

    //  Allocate Led Remote View
    gui_manager->led_remote_view = led_remote_view_alloc(app);

    // Add Led Remote View to the View Dispatcher
    view_dispatcher_add_view(
        gui_manager->view_dispatcher,
        IrGuiRemotesLedRemoteView,
        gui_manager->led_remote_view->view);

    return gui_manager;
}

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

    // Free GUI Manager
    free(gui_manager);
}