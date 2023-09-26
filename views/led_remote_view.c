#include "../ir_gui_remotes.h"
#include "led_remote_view.h"

/**
 * Draw Led Remote View
 * 
 * @param canvas Canvas to draw on
 * @param model Model to draw
 * 
 * @return void
*/
static void led_remote_view_draw_callback(Canvas* canvas, void* model) {
    canvas_clear(canvas);

    // Get Remote Model and Remote
    LedRemoteModel* led_remote_model = (LedRemoteModel*)model;
    LedRemote remote = *led_remote_model->remote;

    // Draw Header
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str_aligned(canvas, 32, 5, AlignCenter, AlignCenter, remote.label);
    canvas_draw_line(canvas, 0, 12, 128, 12);

    // Draw Buttons
    for(int i = 0; i < remote.rows; i++) {
        for(int j = 0; j < remote.cols; j++) {
            LedRemoteButton btn = remote.buttons[(i * remote.cols) + j];
            canvas_draw_icon(
                canvas, j * 16, (i * 17) + 15,
                (led_remote_model->selected_btn == (i * remote.cols) + j) ? btn.icon_hover : btn.icon);
        }
    }
    if (remote.buttons[led_remote_model->selected_btn].label != NULL) {
        canvas_set_font(canvas, FontSecondary);
        canvas_draw_str_aligned(canvas, 32, 123, AlignCenter, AlignCenter, remote.buttons[led_remote_model->selected_btn].label);
    };
}

/**
 * Handle Inputs inside Led Remote View
 * 
 * @param input_event Input Event
 * @param context App context
 * 
 * @return bool True if input was consumed, false otherwise
*/
static bool led_remote_view_input_callback(InputEvent* input_event, void* context) {
    // Get App
    App* app = context;
    // Flag to indicate if input was consumed
    bool consumed = false;
    // Flag to indicate if model was changed
    bool model_changed = false;

    // Get Remote View, Model and Remote
    LedRemoteView* led_remote_view = app->gui_manager->led_remote_view;
    LedRemoteModel* remote_model = view_get_model(led_remote_view->view);
    LedRemote remote = *remote_model->remote;

    // Handle Inputs
    if(input_event->type == InputTypeShort) { // Short Press

        if(input_event->key == InputKeyLeft) { // Left Key
            // Get current row
            int current_row = remote_model->selected_btn / remote.cols;
            // Get min button index of current row
            int min_value = current_row * remote.cols;

            // Set selected button to the left button (or wrap around)
            remote_model->selected_btn = (remote_model->selected_btn - min_value + (-1 % remote.cols) + remote.cols) % remote.cols + min_value;

            // Model changed
            model_changed = true;
            // Consume input
            consumed = true;
        }

        if(input_event->key == InputKeyRight) { // Right Key
            // Get current row
            int current_row = remote_model->selected_btn / remote.cols;
            // Get min button index of current row
            int min_value = current_row * remote.cols;

            // Set selected button to the right button (or wrap around)
            remote_model->selected_btn = (remote_model->selected_btn - min_value + (1 % remote.cols) + remote.cols) % remote.cols + min_value;

            // Model changed
            model_changed = true;
            // Consume input
            consumed = true;
        }

        if(input_event->key == InputKeyUp) { // Up Key

            // Set selected button to the button above (or wrap around)
            remote_model->selected_btn = (remote_model->selected_btn + (-remote.cols % (remote.cols * remote.rows)) + (remote.cols * remote.rows)) % (remote.cols * remote.rows);

            // Model changed
            model_changed = true;
            // Consume input
            consumed = true;
        }

        if(input_event->key == InputKeyDown) { // Down Key

            // Set selected button to the button below (or wrap around)
            remote_model->selected_btn = (remote_model->selected_btn + (remote.cols % (remote.cols * remote.rows)) + (remote.cols * remote.rows)) % (remote.cols * remote.rows);

            // Model changed
            model_changed = true;
            // Consume input
            consumed = true;
        }

        // If isset color in button, change led color
        if(remote.buttons[remote_model->selected_btn].color != 0) {
            int hexColor = remote.buttons[remote_model->selected_btn].color;
            turn_on_led(app, hexColor);  
        } else {
            turn_off_led(app);
        }
    }

    if(input_event->key == InputKeyOk) { // OK Key

        if(input_event->type == InputTypePress) { // Press -> Start transmitting
            // Get Infrared Message
            InfraredMessage ir_message = remote.buttons[(remote_model->selected_btn)].ir_message;
            
            notification_message(app->notifications, &sequence_blink_start_red);
               
            // Start transmitting
            start_ir_transmission(&ir_message, app);

            // Consume input
            consumed = true;
        } else if(input_event->type == InputTypeRelease) { // Release -> Stop transmitting
            // Send Notification (Stop Blinking Red Led)
            notification_message(app->notifications, &sequence_blink_stop);

            // Stop transmitting
            stop_ir_transmission(app);

            // If isset color in button, change led color
            if(remote.buttons[remote_model->selected_btn].color != 0) {
                int hexColor = remote.buttons[remote_model->selected_btn].color;
                turn_on_led(app, hexColor);  
            } else {
                turn_off_led(app);
            }

            // Consume input
            consumed = true;
        }
    }

    // Commit Model if it's changed
    if(model_changed) view_commit_model(led_remote_view->view, false);

    return consumed;
}

/**
 * Allocate Led Remote View
 * 
 * @param app App context
 * 
 * @return LedRemoteView* Led Remote View
*/
LedRemoteView* led_remote_view_alloc(App* app) {
    // Allocate Led Remote View
    LedRemoteView* led_remote_view = malloc(sizeof(LedRemoteView));

    led_remote_view->app = app;

    // Allocate View
    led_remote_view->view = view_alloc();

    // Allocate Model
    view_allocate_model(led_remote_view->view, ViewModelTypeLockFree, sizeof(LedRemoteModel));

    // Set Led Remote View Context
    view_set_context(led_remote_view->view, app);
    // Set Led Remote View Orientation
    view_set_orientation(led_remote_view->view, ViewOrientationVertical);

    // Set View Callbacks
    view_set_input_callback(led_remote_view->view, led_remote_view_input_callback);
    view_set_draw_callback(led_remote_view->view, led_remote_view_draw_callback);

    return led_remote_view;
}

/**
 * Free Led Remote View
 * 
 * @param app App context
 * 
 * @return void
*/
void led_remote_view_free(LedRemoteView* led_remote_view) {
    // Free View
    view_free(led_remote_view->view);

    // Free Led Remote View
    free(led_remote_view);
}