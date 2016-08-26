#include "goldlucks.h"
void
popup_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *popup = data;
   evas_object_del(popup);
}

void
list_item_clicked1(void *data, Evas_Object *obj, void *event_info) {
   //Evas_Object *win = data;
   /* popup */
   Evas_Object *popup;
   Evas_Object *btn1;
   popup = elm_popup_add(data);
   elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
   eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
   evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_text_set(popup,"'Analysis' button is clicked");
   /* ok button */
   btn1 = elm_button_add(popup);
   elm_object_style_set(btn1, "popup");
   elm_object_text_set(btn1, "OK");
   elm_object_part_content_set(popup, "button1", btn1);
   evas_object_smart_callback_add(btn1, "clicked", popup_btn_clicked_cb, popup);
   evas_object_show(popup);
}
void
list_item_clicked2(void *data, Evas_Object *obj, void *event_info) {
   //Evas_Object *win = data;
   /* popup */
   Evas_Object *popup;
   Evas_Object *btn1;
   popup = elm_popup_add(data);
   elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
   eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
   evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_text_set(popup,"'To Share' button is clicked");
   /* ok button */
   btn1 = elm_button_add(popup);
   elm_object_style_set(btn1, "popup");
   elm_object_text_set(btn1, "OK");
   elm_object_part_content_set(popup, "button1", btn1);
   evas_object_smart_callback_add(btn1, "clicked", popup_btn_clicked_cb, popup);
   evas_object_show(popup);
}
void
list_item_clicked3(void *data, Evas_Object *obj, void *event_info) {
   /* popup */
   Evas_Object *popup;
   Evas_Object *btn1;
   popup = elm_popup_add(data);
   elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
   eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
   evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_text_set(popup,"'Fixed Expenses' button is clicked");

   /* ok button */
   btn1 = elm_button_add(popup);
   elm_object_style_set(btn1, "popup");
   elm_object_text_set(btn1, "OK");
   elm_object_part_content_set(popup, "button1", btn1);
   evas_object_smart_callback_add(btn1, "clicked", popup_btn_clicked_cb, popup);
   evas_object_show(popup);
}
void
list_item_clicked4(void *data, Evas_Object *obj, void *event_info) {
   /* popup */
   Evas_Object *popup;
   Evas_Object *btn1;
   popup = elm_popup_add(data);
   elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
   eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, eext_popup_back_cb, NULL);
   evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_text_set(popup,"'Settings' button is clicked");

   /* ok button */
   btn1 = elm_button_add(popup);
   elm_object_style_set(btn1, "popup");
   elm_object_text_set(btn1, "OK");
   elm_object_part_content_set(popup, "button1", btn1);
   evas_object_smart_callback_add(btn1, "clicked", popup_btn_clicked_cb, popup);
   evas_object_show(popup);
}
