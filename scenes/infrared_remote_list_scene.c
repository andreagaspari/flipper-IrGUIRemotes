#include "infrared_remote_list_scene.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <m-array.h>
#include <toolbox/path.h>
#include <storage/storage.h>
#include <core/common_defines.h>

void infrared_remote_list_scene_on_enter(void* context) {
    App* app = context;
    
    DialogsFileBrowserOptions browser_options;
    dialog_file_browser_set_basic_options(&browser_options, INFRARED_APP_EXTENSION, &I_remote_10x10);
    browser_options.skip_assets = true;
    browser_options.base_path = INFRARED_APP_FOLDER;

    bool success = dialog_file_browser_show(
        app->dialogs, app->file_path, app->file_path, &browser_options);

    
    if(success) {
        // Get Model and set Led Sign Remote
        InfraredGuiRemoteModel* remote_model = view_get_model(app->gui_manager->infrared_gui_remote_view->view);
        InfraredGuiRemote* remote = app->remote;

        // Set File Path
        remote_model->file_path = app->file_path;

        // TODO: Load remote
        //Storage* storage = furi_record_open(RECORD_STORAGE);
        //FlipperFormat* ff = flipper_format_buffered_file_alloc(storage);

        FuriString* buf;
        buf = furi_string_alloc();

        bool success = false;

        do {
            // if(!flipper_format_buffered_file_open_existing(ff, furi_string_get_cstr(path))) break;

            path_extract_filename(remote_model->file_path, buf, true);
            remote->label = furi_string_get_cstr(buf);
    
            success = true;
        } while(false);
        

        remote_model->remote = app->remote;
        view_commit_model(app->gui_manager->infrared_gui_remote_view->view, false);
    }

    if(success) {
        scene_manager_next_scene(app->gui_manager->scene_manager, IrGuiRemotesInfraredRemoteScene);
    } else {
        scene_manager_previous_scene(app->gui_manager->scene_manager);
    }
}

bool infrared_remote_list_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    bool consumed = false;

    return consumed;
}

void infrared_remote_list_scene_on_exit(void* context) {
    UNUSED(context);
}
