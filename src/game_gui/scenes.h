#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include <gui/scene_manager.h>

#include "loading_scene.h"
#include "main_scene.h"
#include "settings_scene.h"

enum Scenes {
    scene_loading,
    scene_main,
    scene_settings,
    scene_count // its enum value is the number of elements that preceeds it
};

static void (*const scene_on_enter_handlers[])(void *) = {
    scene_loading_on_enter,
    scene_main_on_enter,
    scene_settings_on_enter};
static bool (*const scene_on_event_handlers[])(void *, SceneManagerEvent) = {
    scene_loading_on_event,
    scene_main_on_event,
    scene_settings_on_event};
static void (*const scene_on_exit_handlers[])(void *) = {
    scene_loading_on_exit,
    scene_main_on_exit,
    scene_settings_on_exit};

static const SceneManagerHandlers scene_handlers = {
    .on_enter_handlers = scene_on_enter_handlers,
    .on_event_handlers = scene_on_event_handlers,
    .on_exit_handlers = scene_on_exit_handlers,
    .scene_num = scene_count};

#endif
