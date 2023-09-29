#ifndef INFRARED_GUI_REMOTE_VIEW_H
#define INFRARED_GUI_REMOTE_VIEW_H

#pragma once

#include <gui/view.h>
#include "../ir_gui_remotes.h"

typedef struct App App;
typedef struct InfraredGuiRemote InfraredGuiRemote;

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