#include "infrared_remote_list_scene.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <m-array.h>
#include <toolbox/path.h>
#include <storage/storage.h>
#include <core/common_defines.h>

void infrared_remote_scene_on_enter(void* context) {
    App* app = context;
    
    view_dispatcher_switch_to_view(app->gui_manager->view_dispatcher, IrGuiRemotesInfraredGuiRemoteView);
}

bool infrared_remote_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    bool consumed = false;

    return consumed;
}

void infrared_remote_scene_on_exit(void* context) {
    UNUSED(context);
}
