/**
 * \file
 *
 * \brief Settings widget for the SAM toolkit demo application
 *
 * Copyright (c) 2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 */
 
#include "demo.h"
#include <asf.h>
#include "string.h"
#include "bitmaps.h"

/**
 * \brief Command event IDs for the settings widgets
 */
enum settings_command_id {
	/** Dummy icon */
	ICON_DUMMY_ID = 0,
	/** Command event ID for time settings icon button */
	ICON_SETTINGS_TIME_ID,
	/** Command event ID for date settings icon button */
	ICON_SETTINGS_DATE_ID,
	/** Command event ID for backlight settings icon button */
	ICON_SETTINGS_BACKLIGHT_ID,
	/** Command event ID for touch calibration settings button */
	ICON_SETTINGS_TSD_ID,
	/** Command event ID for return icon button */
	ICON_SETTINGS_RET_ID,
	/**Max settings icon number */
	ICON_SETTINGS_MAX_ID,
};

/** Widget application context */
struct widget_context_settings {
	/** Pointer to frame for application */
	struct wtk_basic_frame *frame;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/** Pointer to frame for logo */
	struct wtk_basic_frame *logo_frame;
	/** Label widget for board name */
	struct wtk_label *lbl_board_name;
	/** Label widget for function name string */
	struct wtk_label *lbl_func_name;
	/* Group of icon button widgets */
	struct wtk_icon_group *icon_group;
	/* Array if icon button widgets */
	struct wtk_icon_button *icons[ICON_SETTINGS_MAX_ID];
};

/** Statically allocated context pointer */
static struct widget_context_settings *widget_ctx_settings;

/** Function name of the settings widget*/
static char demo_func_name[] = "Demo Settings";

/**  Logo bitmap */
static struct gfx_bitmap win_root_logo_icon = {
	.width = 87, .height=40,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_LOGO_ATMEL
};

/** Time settings bitmap */
static struct gfx_bitmap win_settings_time_icon = {
	.width = 64, .height=64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_TIME_SETUP
};


/** Date settings bitmap */
static struct gfx_bitmap win_settings_date_icon = {
	.width = 56, .height=56,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_DATE_SETUP
};

/** Backlight settings bitmap */
static struct gfx_bitmap win_settings_backlight_icon = {
	.width = 64, .height=64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_BACKLIGHT_SETUP
};

/** Touch calibration settings bitmap */
static struct gfx_bitmap win_settings_tsd_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_TSD_SETUP
};

/** Return bitmap */
static struct gfx_bitmap win_settings_ret_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_BACK
};

/**
 * \brief Frame handler for the application
 *
 * Handles all command events from the widgets in the application frame.
 *
 * \param frame Pointer to the application frame
 * \param command_data Command event ID
 *
 * \return True if exiting, to destroy the window
 */
static bool widget_settings_frame_command_handler(struct wtk_basic_frame *frame,
		win_command_t command_data)
{
	char command;
	command = (uintptr_t)command_data;

	/* Remove warnings */
	UNUSED(frame);

	switch (command) {
	case ICON_SETTINGS_TIME_ID:
		/* Launch time settings widget */
		app_widget_settings_on(false);
		app_widget_settings_time_on(true);
		break;

	case ICON_SETTINGS_DATE_ID:
		/* Launch date settings widget */
		app_widget_settings_on(false);
		app_widget_settings_date_on(true);
		break;

	case ICON_SETTINGS_BACKLIGHT_ID:
		/* Launch backlight settings widget */
		app_widget_settings_on(false);
		app_widget_settings_backlight_on(true);
		break;

	case ICON_SETTINGS_TSD_ID:
		/* Launch touch calibration settings widget */
		demo_set_special_mode_status(DEMO_LCD_CALIBRATE_MODE, 1);
		break;

	case ICON_SETTINGS_RET_ID:
		/* Turn off settings widget */
		app_widget_settings_on(false);

		/* Turn on main widget */
		app_widget_main_on(true);
		break;
	}
	return false;
}


/**
 * \brief Setup settings widget
 *
 * Allocates memory for the application context, and creates all widgets that
 * make up its interface. If memory allocation or widget creation fails, the
 * application exits immediately.
 */
static void app_widget_launch_settings(void)
{
	struct win_window *parent;
	struct win_area area;

	/* Create a new context for the GUI, clear new context state */
	widget_ctx_settings = membag_alloc(sizeof(struct widget_context_settings));

	/* Set the background information for the GUI window */
	widget_ctx_settings->frame_bg.type = GFX_BITMAP_SOLID;
	widget_ctx_settings->frame_bg.data.color = GFX_COLOR(255, 255, 255);

	/* Set the area for the GUI window */
	area = win_get_attributes(win_get_root())->area;

	/* Create and show the main GUI frame */
	widget_ctx_settings->frame = wtk_basic_frame_create(
			win_get_root(), &area, &widget_ctx_settings->frame_bg, NULL,
			widget_settings_frame_command_handler, widget_ctx_settings);
	if (!widget_ctx_settings->frame) {
		goto error_frame;
	}

	parent = wtk_basic_frame_as_child(widget_ctx_settings->frame);
	win_show(parent);

	/* Set the area for the logo*/
	area.pos.x = 0;
	area.pos.y = 0;
	area.size.x = 87;
	area.size.y = 40;
	/* Create and show the main GUI frame */
	widget_ctx_settings->logo_frame = wtk_basic_frame_create(
			parent, &area, &win_root_logo_icon, NULL,
			NULL, NULL);
	if (!widget_ctx_settings->frame) {
		goto error_frame;
	}

	win_show(wtk_basic_frame_as_child(widget_ctx_settings->logo_frame));

	/* Set the area for the board name label */
	area.pos.x = 100;
	area.pos.y = 0;
	wtk_label_size_hint(&area.size, demo_board_name);

	/* Create label inside frame */
	widget_ctx_settings->lbl_board_name = wtk_label_create(
			parent, &area, demo_board_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings->lbl_board_name) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_settings->lbl_board_name));

	/* Set the area for the function name label */
	area.pos.x = 100;
	area.pos.y = 20;
	wtk_label_size_hint(&area.size, demo_func_name);

	/* Create label inside frame */
	widget_ctx_settings->lbl_func_name = wtk_label_create(
			parent, &area, demo_func_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings->lbl_func_name) {
		goto error_widget;
	}
	
	win_show(wtk_label_as_child(widget_ctx_settings->lbl_func_name));

	/* Create a logical group for the icon buttons */
	widget_ctx_settings->icon_group = wtk_icon_group_create();
	if (!widget_ctx_settings->icon_group) {
		goto error_widget;
	}

	/* Set the area for the time settings icon button widget */
	area.pos.x = 16;
	area.pos.y = 81;
	area.size.x = 0;
	wtk_icon_button_size_hint(&area.size, &win_settings_time_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings->icons[ICON_SETTINGS_TIME_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_time_icon, false, widget_ctx_settings->icon_group,
			(win_command_t)(ICON_SETTINGS_TIME_ID));
	if (!widget_ctx_settings->icons[ICON_SETTINGS_TIME_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings->icons[ICON_SETTINGS_TIME_ID]));


	/* Set the area for the date settings widget */
	area.pos.x = 98;
	area.pos.y = 90;
	wtk_icon_button_size_hint(&area.size, &win_settings_date_icon);

	/* Create the date settings icon button inside frame */
	widget_ctx_settings->icons[ICON_SETTINGS_DATE_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_date_icon, false, widget_ctx_settings->icon_group,
			(win_command_t)(ICON_SETTINGS_DATE_ID));
	if (!widget_ctx_settings->icons[ICON_SETTINGS_DATE_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings->icons[ICON_SETTINGS_DATE_ID]));

	/* Set the area for the backlight settings widget */
	area.pos.x = 165;
	area.pos.y = 86;
	wtk_icon_button_size_hint(&area.size, &win_settings_backlight_icon);

	/* Create the backlight settings icon button inside frame */
	widget_ctx_settings->icons[ICON_SETTINGS_BACKLIGHT_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_backlight_icon, false, widget_ctx_settings->icon_group,
			(win_command_t)(ICON_SETTINGS_BACKLIGHT_ID));
	if (!widget_ctx_settings->icons[ICON_SETTINGS_BACKLIGHT_ID]) {
		goto error_widget;
	}
	
	win_show(wtk_icon_button_as_child(widget_ctx_settings->icons[ICON_SETTINGS_BACKLIGHT_ID]));

	/* Set the area for the touch calibration widget */
	area.pos.x = 100;
	area.pos.y = 180;
	wtk_icon_button_size_hint(&area.size, &win_settings_tsd_icon);

	/* Create the touch calibration icon button inside frame */
	widget_ctx_settings->icons[ICON_SETTINGS_TSD_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_tsd_icon, false, widget_ctx_settings->icon_group,
			(win_command_t)(ICON_SETTINGS_TSD_ID));
	if (!widget_ctx_settings->icons[ICON_SETTINGS_TSD_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings->icons[ICON_SETTINGS_TSD_ID]));

	/* Set the area for the return icon */
	area.pos.x = 12;
	area.pos.y = 232;
	wtk_icon_button_size_hint(&area.size, &win_settings_ret_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings->icons[ICON_SETTINGS_RET_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_ret_icon, false, widget_ctx_settings->icon_group,
			(win_command_t)(ICON_SETTINGS_RET_ID));
	if (!widget_ctx_settings->icons[ICON_SETTINGS_RET_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings->icons[ICON_SETTINGS_RET_ID]));
	return;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(widget_ctx_settings->frame));
error_frame:
	membag_free(widget_ctx_settings);
}

/**
 * \brief Enable/disable settings widget.
 *
 * \param on Turn on/off settings widget.
 */
void app_widget_settings_on(uint8_t on)
{
	if (on) {
		app_widget_launch_settings();
	} else {
		if (widget_ctx_settings->frame) {
			win_destroy(wtk_basic_frame_as_child(widget_ctx_settings->frame));
		}
	}

}
