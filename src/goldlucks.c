#include "goldlucks.h"

typedef struct appdata {
	/*Evas_Object *win;
	Evas_Object *conform;*/
	Evas_Object *label;

	const char *name;
	Evas_Object *win;
	Evas_Object *conform;

	Evas_Object *nf;
	Evas_Object *scroller;
	Evas_Object *tabbar;

	Evas_Object *first_view_rect;
	Evas_Object *second_view_rect;
	Evas_Object *third_view_rect;
	Evas_Object *fourth_view_rect;

	Evas_Object	*gl_income; //from income_view
//	sqlite3 *income_db; // Database handle
} appdata_s;

static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

static void
win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Let window go to hide state. */
	elm_win_lower(ad->win);
}
static Evas_Object *
create_conform(Evas_Object *parent)
{
	Evas_Object *conform, *bg;

	if (parent == NULL) return NULL;

	conform = elm_conformant_add(parent);
	evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(parent, conform);

	bg = elm_bg_add(conform);
	elm_object_style_set(bg, "indicator/headerbg");
	elm_object_part_content_set(conform, "elm.swallow.indicator_bg", bg);
	evas_object_show(bg);

	evas_object_show(conform);
	return conform;
}

static Evas_Object *
create_drawer_layout(Evas_Object *parent)
{
	Evas_Object *layout;
	layout = elm_layout_add(parent);
	elm_layout_theme_set(layout, "layout", "drawer", "panel");
	evas_object_show(layout);

	return layout;
}

//income_view에서 저장한 내용 출
//Evas_Object *ui_utils_create_genlist(Evas_Object *parent)
//{
//	Evas_Object *gen_list = elm_genlist_add(parent);
//	elm_genlist_mode_set(gen_list, ELM_LIST_COMPRESS);
//	return gen_list;
//}

static Evas_Object *
create_main_view(appdata_s *ad)
{
	Evas_Object *layout, *box, *box2;
	Evas_Object *first_view, *second_view, *third_view, *fourth_view;

	/* Layout for drawer */
	layout = create_drawer_layout(ad->nf);

	/* Box */
	box = elm_box_add(layout);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_part_content_set(layout, "elm.swallow.content", box);

	/*Income label*/
	Evas_Object *label_income = elm_label_add(box);
	evas_object_size_hint_weight_set(label_income, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(label_income, EVAS_HINT_FILL, EVAS_HINT_FILL);
	//elm_object_part_content_set(ad->nf, "elm.swallow.label.events", label_income);
	elm_object_text_set(label_income, "<font_size=70>Income</font_size>");
	evas_object_color_set(label_income, 0, 0, 0, 255);
	elm_box_pack_end(box, label_income);
	evas_object_show(label_income);

//	/*Create genlist Income from income_view*/
//	ad->gl_income = ui_utils_create_genlist(layout);
//	evas_object_size_hint_weight_set(ad->gl_income, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
//	evas_object_size_hint_align_set(ad->gl_income, EVAS_HINT_FILL, EVAS_HINT_FILL);
//	elm_object_part_content_set(layout, "elm.swallow.genlist.events", ad->gl_income);
//	evas_object_show(ad->gl_income);


	return layout;
}

static Evas_Object *
create_bg(Evas_Object *parent)
{
	Evas_Object *rect;
	rect = evas_object_rectangle_add(evas_object_evas_get(parent));
	evas_object_color_set(rect, 0, 0, 0, 0);
	evas_object_show(rect);

	return rect;
}

static Evas_Object *
create_panel(Evas_Object *parent)
{
	Evas_Object *panel, *list;
	int i;
	char buf[64];

	/* Panel */
	panel = elm_panel_add(parent);
	elm_panel_scrollable_set(panel, EINA_TRUE);

	/* Default is visible, hide the content in default. */
	elm_panel_hidden_set(panel, EINA_TRUE);
	elm_panel_orient_set(panel, ELM_PANEL_ORIENT_LEFT);
	evas_object_show(panel);

	/* Panel content */
	list = elm_list_add(panel);
	evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);

	sprintf(buf, "<font_size=80>Gold Lucks</font_size>");
	elm_list_item_append(list, buf, NULL, NULL, NULL,NULL);
	sprintf(buf, "ANALYSIS");
	elm_list_item_append(list, buf, NULL, NULL, list_item_clicked1, parent);
	sprintf(buf, "TO SHARE");
	elm_list_item_append(list, buf, NULL, NULL, list_item_clicked2, parent);
	sprintf(buf, "FIXED EXPENSES");
	elm_list_item_append(list, buf, NULL, NULL, list_item_clicked3, parent);
	sprintf(buf, "SETTINGS");
	elm_list_item_append(list, buf, NULL, NULL, list_item_clicked4, parent);
	evas_object_show(list);

	elm_object_content_set(panel, list);
	evas_object_show(panel);
	return panel;
}

static void
drawer_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_panel_hidden_set(obj, EINA_TRUE);
}

static void
panel_scroll_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Panel_Scroll_Info *ev = event_info;
	Evas_Object *bg = data;
	int col = 127 * ev->rel_x;

	evas_object_color_set(bg, 0, 0, 0, col);
}

static Evas_Object *
create_drawers_btn(Evas_Object *parent, Evas_Smart_Cb func, void *data)
{
	Evas_Object *btn = elm_button_add(parent);
	if (!btn) return NULL;
	elm_object_style_set(btn, "naviframe/drawers");
	evas_object_smart_callback_add(btn, "clicked", func, data);

	return btn;
}

static void
view_size_reset(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	Evas_Coord w, h;

	evas_object_geometry_get(ad->win, NULL, NULL, &w, NULL);
	evas_object_geometry_get(ad->scroller, NULL, NULL, NULL, &h);

	elm_scroller_page_size_set(ad->scroller, w, h);
	evas_object_size_hint_min_set(ad->first_view_rect, w, h);
	evas_object_size_hint_min_set(ad->second_view_rect, w, h);
	evas_object_size_hint_min_set(ad->third_view_rect, w, h);
	evas_object_size_hint_min_set(ad->fourth_view_rect, w, h);
}
static void
btn_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *panel = data;
	if (!elm_object_disabled_get(panel)) elm_panel_toggle(panel);
}


/*ctxpopup list를 button 근처로 옮겨주는 함수*/
static void
move_ctxpopup(Evas_Object *ctxpopup, Evas_Object *btn)
{
	Evas_Coord x, y, w , h;
	evas_object_geometry_get(btn, &x, &y, &w, &h);
	evas_object_move(ctxpopup, x + (w / 2), y + (h / 2));
}

static void
ctxpopup_dismissed_cb(void *data, Evas_Object *obj, void *event_info)
{
	evas_object_del(obj);
	obj = NULL;
}


/*ctxpopup 콜백함수*/
static void
main_btn2_cb(void *data, Evas_Object *obj, void *event_info){

	Evas_Object *nf = data;
	Evas_Object *ctxpopup;
	evas_object_del(ctxpopup);
	ctxpopup = elm_ctxpopup_add(nf);

	eext_object_event_callback_add(ctxpopup, EEXT_CALLBACK_BACK, eext_ctxpopup_back_cb, NULL);
	evas_object_smart_callback_add(ctxpopup,"dismissed", ctxpopup_dismissed_cb, NULL);

	elm_ctxpopup_item_append(ctxpopup, "+ income", NULL, income_view_cb, nf);
	elm_ctxpopup_item_append(ctxpopup, "- expense", NULL, expense_view_cb, nf);
	elm_ctxpopup_item_append(ctxpopup, " memo", NULL, memo_view_cb, nf);

	move_ctxpopup(ctxpopup, obj);
	evas_object_show(ctxpopup);

}


static void
create_base_gui(appdata_s *ad)
{
	Evas_Object *layout, *bg, *drawer, *btn;
	Elm_Object_Item *nf_it;

	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_conformant_set(ad->win, EINA_TRUE);
	elm_win_autodel_set(ad->win, EINA_TRUE);
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);

	evas_object_smart_callback_add(ad->win, "delete,request",
			win_delete_request_cb, NULL);
	eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb,
			ad);

	ad->conform = create_conform(ad->win);

	/* Naviframe */
	ad->nf = elm_naviframe_add(ad->conform);
	elm_object_content_set(ad->conform, ad->nf);

	layout = create_main_view(ad);
	evas_object_show(layout);

	nf_it = elm_naviframe_item_push(ad->nf, "Gold Lucks", NULL, NULL, layout,"basic");

	/* Drawer bg */
	bg = create_bg(layout);
	elm_object_part_content_set(layout, "elm.swallow.bg", bg);

	/* Drawer */
	drawer = create_panel(layout);
	eext_object_event_callback_add(drawer, EEXT_CALLBACK_BACK, drawer_back_cb,
			ad);
	evas_object_smart_callback_add(drawer, "scroll", panel_scroll_cb, bg);
	elm_object_part_content_set(layout, "elm.swallow.left", drawer);

	/* Drawers Button */
	btn = create_drawers_btn(ad->nf, btn_cb, drawer);
	elm_object_item_part_content_set(nf_it, "title_left_btn", btn);

	btn = elm_button_add(ad->nf);
	elm_object_style_set(btn,"naviframe/title_right");
	evas_object_smart_callback_add(btn,"clicked",main_btn2_cb,ad->nf);
	elm_object_item_part_content_set(nf_it,"title_right_btn",btn);
	elm_object_text_set(btn, "<align=center> <font_size=80> + </align></font_size>");



	/* Show window after base gui is set up */
	evas_object_show(ad->win);

	evas_object_event_callback_add(ad->win, EVAS_CALLBACK_RESIZE,
			view_size_reset, ad);

}

static bool
app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
		Initialize UI resources and application's data
		If this function returns true, the main loop of application starts
		If this function returns false, the application is terminated */
	appdata_s *ad = data;

	create_base_gui(ad);

	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data)
{
	/* Release all resources. */
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad);

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

	return ret;
}
