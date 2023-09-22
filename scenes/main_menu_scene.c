#include "main_menu_scene.h"

/**
 * Main Menu Handlers
 * 
 * @param context App context
 * @param index Index of the selected item
 * 
 * @return void
*/
void main_menu_scene_callback(void* context, uint32_t index) {
    App* app = context;

    // Handle selected item
    switch(index) {
    case IrGuiRemotesMainMenuSceneLedStripe: // Led Stripe
        // Send custom event to scene manager
        scene_manager_handle_custom_event(
            app->scene_manager, IrGuiRemotesMainMenuSceneLedStripeEvent);
        break;
    case IrGuiRemotesMainMenuSceneLedSign: // Led Sign
        // Send custom event to scene manager
        scene_manager_handle_custom_event(
            app->scene_manager, IrGuiRemotesMainMenuSceneLedSignEvent);
        break;
    }
}

/**
 * Setup and draw the Main Menu
 * 
 * @param context App context
 * 
 * @return void
*/
void main_menu_scene_on_enter(void* context) {
    App* app = context;

    // Reset Submenu
    submenu_reset(app->submenu);
    // Set Header
    submenu_set_header(app->submenu, "LED Remotes");
    // Add Items
    submenu_add_item(
        app->submenu,
        "LED Stripe",
        IrGuiRemotesMainMenuSceneLedStripe,
        main_menu_scene_callback,
        app);
    submenu_add_item(
        app->submenu, "LED Sign", IrGuiRemotesMainMenuSceneLedSign, main_menu_scene_callback, app);

    // Switch to Submenu View
    view_dispatcher_switch_to_view(app->view_dispatcher, IrGuiRemotesMainMenuView);
}

/**
 * Handle Events inside Main Menu
 * 
 * @param context App context
 * @param event Event to handle
 * 
 * @return bool True if event was consumed, false otherwise
*/
bool main_menu_scene_on_event(void* context, SceneManagerEvent event) {
    App* app = context;
    bool consumed = false;

    switch(event.type) {
    case SceneManagerEventTypeCustom:
        switch(event.event) {
        case IrGuiRemotesMainMenuSceneLedStripeEvent: // Led Stripe
            // Switch to Led Stripe Scene
            scene_manager_next_scene(app->scene_manager, IrGuiRemotesLedStripeScene);
            consumed = true;
            break;
        case IrGuiRemotesMainMenuSceneLedSignEvent: // Led Sign
            // Switch to Led Sign Scene
            scene_manager_next_scene(app->scene_manager, IrGuiRemotesLedSignScene);
            consumed = true;
            break;
        }
        break;
    default:
        break;
    }

    return consumed;
}

/**
 * Cleanup Main Menu on Exit
 * 
 * @param context App context
 * 
 * @return void
*/
void main_menu_scene_on_exit(void* context) {
    App* app = context;
    // Reset Submenu
    submenu_reset(app->submenu);
}
