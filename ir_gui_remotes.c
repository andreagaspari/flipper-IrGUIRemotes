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

    // Allocate GUI Manager
    app->gui_manager = gui_manager_alloc(app);

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

    // Free GUI Manager
    gui_manager_free(app->gui_manager);

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
    view_dispatcher_attach_to_gui(
        app->gui_manager->view_dispatcher, gui, ViewDispatcherTypeFullscreen);
    // Switch to Main Menu Scene
    scene_manager_next_scene(app->gui_manager->scene_manager, IrGuiRemotesMainMenuView);
    // Run View Dispatcher
    view_dispatcher_run(app->gui_manager->view_dispatcher);

    // Free App on exit
    app_free(app);
    return 0;
}