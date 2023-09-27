#ifndef INFRARED_GUI_REMOTE_VIEW_H
#define INFRARED_GUI_REMOTE_VIEW_H

#pragma once

#include <gui/view.h>
#include <infrared/worker/infrared_worker.h>

typedef struct App App;

/**
 * Infrared Gui Remote Button Data Structure
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
} InfraredGuiRemoteButton;

/**
 * Infrared Gui Remote Data Structure
 * 
 * @param label Label
 * @param rows Rows
 * @param cols Columns
 * @param buttons Buttons
 * 
*/
typedef struct {
    char* label;
    InfraredGuiRemoteButton* buttons;
} InfraredGuiRemote;

/**
 * Infrared Gui Remote Model
 * 
 * @param remote Remote
 * @param selected_btn Selected Button
*/
typedef struct InfraredGuiRemoteModel {
    InfraredGuiRemote* remote;
    uint32_t selected_btn;
    FuriString* file_path;
} InfraredGuiRemoteModel;


/**
 * Infrared Gui Remote View
 * 
 * @param app App data
 * @param view View
*/
typedef struct InfraredGuiRemoteView {
    App* app;
    View* view;
} InfraredGuiRemoteView;

/**
 * Infrared Gui Remote View Allocation
 * 
 * @param app App data
 * 
 * @return InfraredGuiRemoteView* Infrared Gui Remote View
*/
InfraredGuiRemoteView* infrared_gui_remote_view_alloc(App* app);

/**
 * Infrared Gui Remote View free
 * 
 * @param infrared_gui_remote_view Infrared Gui Remote View
*/
void infrared_gui_remote_view_free(InfraredGuiRemoteView* infrared_gui_remote_view);

#endif // INFRARED_GUI_REMOTE_VIEW_H