#include <vlc_common.h>
#include <vlc_plugin.h>
#include <vlc_interface.h>
#include <vlc_modules.h>
#include <vlc_playlist.h>
#include <vlc_atomic.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct intf_sys_t {
    bool b_smart_shuffle;
    bool b_is_jumping;
    int i_current_smart_index;
    int i_total_items;
    int* p_permutation_list;
} intf_sys_t;

static void shuffle_permutation_list(intf_sys_t* sys) {
    for (int i = sys->i_total_items - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = sys->p_permutation_list[i];
        sys->p_permutation_list[i] = sys->p_permutation_list[j];
        sys->p_permutation_list[j] = temp;
    }
}

static void init_permutation_list(intf_sys_t* sys) {
    playlist_t* pl = pl_Get(NULL); 
    if (!pl) return;

    PL_LOCK();
    sys->i_total_items = playlist_GetItemCount(pl);
    PL_UNLOCK();

    if (sys->i_total_items <= 1) return;

    if (sys->p_permutation_list) free(sys->p_permutation_list);
    sys->p_permutation_list = malloc(sizeof(int) * sys->i_total_items);
    
    for (int i = 0; i < sys->i_total_items; i++) sys->p_permutation_list[i] = i;
    shuffle_permutation_list(sys);
    sys->i_current_smart_index = 0;
}

static int on_key_press(vlc_object_t *p_this, char const *name, vlc_value_t oldval, vlc_value_t newval, void *p_data) {
    intf_thread_t *intf = (intf_thread_t*) p_data;
    intf_sys_t *sys = intf->p_sys;

    sys->b_smart_shuffle = !sys->b_smart_shuffle;
    
    if (sys->b_smart_shuffle) {
        var_SetBoolean(intf->obj.libvlc, "playlist-shuffle", false);
        init_permutation_list(sys);
        vlc_msg(vlc_log_get(), VLC_LOG_INFO, "Smart Shuffle Enabled\n");
    } else {
        vlc_msg(vlc_log_get(), VLC_LOG_INFO, "Smart Shuffle Disabled\n");
    }

    return VLC_SUCCESS;
}

static int on_playlist_input_current(vlc_object_t *p_this, char const *name, vlc_value_t oldval, vlc_value_t newval, void *p_data) {
    intf_thread_t *intf = (intf_thread_t*) p_data;
    intf_sys_t *sys = intf->p_sys;

    if (!sys->b_smart_shuffle || sys->b_is_jumping) return VLC_SUCCESS;
    if (sys->i_total_items <= 1) return VLC_SUCCESS;

    sys->b_is_jumping = true;

    if (sys->i_current_smart_index >= sys->i_total_items) {
        shuffle_permutation_list(sys);
        sys->i_current_smart_index = 0;
    }

    int next_index = sys->p_permutation_list[sys->i_current_smart_index];
    var_SetInteger(pl_Get(intf), "item-current", next_index);
    
    sys->i_current_smart_index++;
    sys->b_is_jumping = false;

    return VLC_SUCCESS;
}

static int plugin_open(vlc_object_t *obj) {
    intf_thread_t *intf = (intf_thread_t *) obj;
    intf->p_sys = calloc(1, sizeof(intf_sys_t));
    if (!intf->p_sys) return VLC_ENOMEM;

    var_AddCallback(intf->obj.libvlc, "key-pressed", on_key_//...
