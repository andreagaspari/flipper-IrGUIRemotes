#ifndef LED_REMOTE_VIEW_H
#define LED_REMOTE_VIEW_H

#pragma once

#include <gui/view.h>
#include <infrared/worker/infrared_worker.h>
#include <notification/notification_messages.h>

typedef struct App App;

// Led Remote Button Data Structure
typedef struct {
    const InfraredMessage ir_message;
    const Icon* icon;
    const Icon* icon_hover;
} LedRemoteButton;

// Led Remote Data Structure
typedef struct {
    const char* label;
    const int rows;
    const int cols;
    const LedRemoteButton* buttons;
} LedRemote;

// Model for the Led Remote View
typedef struct LedRemoteModel {
    const LedRemote* remote;
    uint32_t selected_btn;
} LedRemoteModel;

// View for the Led Remote
typedef struct LedRemoteView {
    App* app;
    View* view;
} LedRemoteView;

LedRemoteView* led_remote_view_alloc(App* app);

void led_remote_view_free(LedRemoteView* led_remote_view);

#endif // LED_REMOTE_VIEW_H