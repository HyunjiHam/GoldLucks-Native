#ifndef __goldlucks_H__
#define __goldlucks_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "goldlucks"

#if !defined(PACKAGE)
#define PACKAGE "org.example.goldlucks"
#endif

void btn_back_cb(void *data,Evas_Object *obj, void *event_info);
void income_view_cb(void *data, Evas_Object *obj, void *event_info);
void expense_view_cb(void *data, Evas_Object *obj, void *event_info);
void memo_view_cb(void *data, Evas_Object *obj, void *event_info);
void list_item_clicked1(void *data, Evas_Object *obj, void *event_info);
void list_item_clicked2(void *data, Evas_Object *obj, void *event_info);
void list_item_clicked3(void *data, Evas_Object *obj, void *event_info);
void list_item_clicked4(void *data, Evas_Object *obj, void *event_info);
void popup_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info);

#endif /* __goldlucks_H__ */
