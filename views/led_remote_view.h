#ifndef LED_REMOTE_VIEW_H
#define LED_REMOTE_VIEW_H

#pragma once

#include <gui/view.h>
#include <infrared/worker/infrared_worker.h>
#include <notification/notification_messages.h>

typedef struct App App;

/**
 * Led Remote Button Data Structure
 * 
 * @param label Button Label
 * @param ir_message Infrared Message
 * @param icon Icon
 * @param icon_hover Icon Hover
*/
typedef struct {
    const char* label;
    const InfraredMessage ir_message;
    const Icon* icon;
    const Icon* icon_hover;
    const int color;
} LedRemoteButton;

/**
 * Led Remote Data Structure
 * 
 * @param label Label
 * @param rows Rows
 * @param cols Columns
 * @param buttons Buttons
 * 
*/
typedef struct {
    const char* label;
    const int rows;
    const int cols;
    const LedRemoteButton* buttons;
} LedRemote;

/**
 * Led Remote Model
 * 
 * @param remote Remote
 * @param selected_btn Selected Button
*/
typedef struct LedRemoteModel {
    const LedRemote* remote;
    uint32_t selected_btn;
} LedRemoteModel;

/**
 * Led Remote View
 * 
 * @param app App data
 * @param view View
*/
typedef struct LedRemoteView {
    App* app;
    View* view;
} LedRemoteView;

/**
 * Led Remote View Allocation
 * 
 * @param app App data
 * 
 * @return LedRemoteView* Led Remote View
*/
LedRemoteView* led_remote_view_alloc(App* app);

/**
 * Led Remote View Free
 * 
 * @param led_remote_view Led Remote View
*/
void led_remote_view_free(LedRemoteView* led_remote_view);

#endif // LED_REMOTE_VIEW_H