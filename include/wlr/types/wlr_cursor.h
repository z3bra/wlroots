#ifndef _WLR_TYPES_CURSOR_H
#define _WLR_TYPES_CURSOR_H
#include <wayland-server.h>
#include <wlr/types/wlr_output.h>
#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_input_device.h>
#include <wlr/xcursor.h>

struct wlr_cursor_state;
//struct wlr_cursor_impl *;

struct wlr_cursor {
    struct wlr_cursor_state *state;
    //struct wlr_cursor_impl *impl;
    int x, y;

    struct {
        struct wl_signal motion;
		struct wl_signal motion_absolute;
		struct wl_signal button;
		struct wl_signal axis;
    } events;
};

struct wlr_cursor *wlr_cursor_init();

void wlr_cursor_destroy(struct wlr_cursor *cur);

void wlr_cursor_set_xcursor(struct wlr_cursor *cur, struct wlr_xcursor *xcur);

void wlr_cursor_warp(struct wlr_cursor *cur, double x, double y);

void wlr_cursor_move(struct wlr_cursor *cur, double delta_x, double delta_y);

/**
 * Attaches this input device to this cursor. The input device must be one of:
 *
 * - WLR_INPUT_DEVICE_POINTER
 * - WLR_INPUT_DEVICE_TOUCH
 * - WLR_INPUT_DEVICE_TABLET_TOOL
 */
void wlr_cursor_attach_input_device(struct wlr_cursor *cur,
    struct wlr_input_device *dev);

void wlr_cursor_detach_input_device(struct wlr_cursor *cur,
    struct wlr_input_device *dev);
/**
 * Uses the given layout to establish the boundaries and movement semantics of
 * this cursor. Cursors without an output layout allow infinite movement in any
 * direction and do not support absolute input events.
 */
void wlr_cursor_attach_output_layout(struct wlr_cursor *cur,
    struct wlr_output_layout *l);

/**
 * Attaches this cursor to the given output, which must be among the outputs in
 * the current output_layout for this cursor. This call is invalid for a cursor
 * without an associated output layout.
 */
void wlr_cursor_map_to_output(struct wlr_cursor *cur, struct wlr_output *output);

/**
 * Maps all input from a specific input device to a given output. The input
 * device must be attached to this cursor and the output must be among the
 * outputs in the attached output layout.
 */
void wlr_cursor_map_input_to_output(struct wlr_cursor *cur,
    struct wlr_input_device *dev, struct wlr_output *output);

/**
 * Maps this cursor to an arbitrary region on the associated wlr_output_layout.
 */
//void wlr_cursor_map_to_region(struct wlr_cursor *cur, struct wlr_geometry *geo);

/**
 * Maps inputs from this input device to an arbitrary region on the associated
 * wlr_output_layout.
 */
//void wlr_cursor_map_input_to_region(struct wlr_cursor *cur, struct wlr_input_device *dev, struct wlr_geometry *geo);

#endif
