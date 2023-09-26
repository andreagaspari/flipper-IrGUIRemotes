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

    // If not transmitting, start
    if(!app->ir_transmitting) {
        // Set message
        infrared_worker_set_decoded_signal(app->ir_worker, ir_message);
        // Set callback
        infrared_worker_tx_set_get_signal_callback(app->ir_worker, infrared_worker_tx_get_signal_steady_callback, app);
        // Start transmitting
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

    // If transmitting, stop
    if(app->ir_transmitting) {
        // Stop transmitting
        infrared_worker_tx_stop(app->ir_worker);
        // Clear callback
        infrared_worker_tx_set_get_signal_callback(app->ir_worker, NULL, NULL);
        app->ir_transmitting = false;
    }
}

/**
 * Turn on Notification LED with Hex color code
 * 
 * @param context App context
 * @param hexColor Hex color code
 * 
 * @return void
*/
void turn_on_led(void* context, int hexColor) {
    App* app = context;

    NotificationMessage notification_led_message_1;
    notification_led_message_1.type = NotificationMessageTypeLedRed;
    NotificationMessage notification_led_message_2;
    notification_led_message_2.type = NotificationMessageTypeLedGreen;
    NotificationMessage notification_led_message_3;
    notification_led_message_3.type = NotificationMessageTypeLedBlue;

    notification_led_message_1.data.led.value = (hexColor >> 16) & 0xFF;
    notification_led_message_2.data.led.value = (hexColor >> 8) & 0xFF;
    notification_led_message_3.data.led.value = hexColor & 0xFF;

    const NotificationSequence notification_sequence = {
        &notification_led_message_1,
        &notification_led_message_2,
        &notification_led_message_3,
        &message_do_not_reset,
        NULL,
    };
    notification_message(app->notifications, &notification_sequence);

    furi_thread_flags_wait(0, FuriFlagWaitAny, 10); // Delay, prevent removal from RAM before LED value set
}

/**
 * Turn off Notification LED
 * 
 * @param context App context
 * 
 * @return void
*/
void turn_off_led(void* context) {
    App* app = context;

    // Reset Led Color
    notification_message(app->notifications, &sequence_reset_red);
    notification_message(app->notifications, &sequence_reset_green);
    notification_message(app->notifications, &sequence_reset_blue);

    furi_thread_flags_wait(0, FuriFlagWaitAny, 30); // Delay, prevent removal from RAM before LED value set
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

    // Setup Notifcations
    app->notifications = furi_record_open(RECORD_NOTIFICATION);

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

    // Close Notifications
    furi_record_close(RECORD_NOTIFICATION);

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

    // Run first Scene of the GUI
    gui_manager_run(app->gui_manager);

    // Free App on exit
    app_free(app);
    return 0;
}
