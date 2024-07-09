/*
 * SPDX-FileCopyrightText: 2016-2016 CSSlayer <wengxt@gmail.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */

#include <locale.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "fcitx-utils/fs.h"
#include "fcitx-utils/log.h"
#include "fcitx-utils/misc.h"
#include "fcitx-utils/misc_p.h"
#include "fcitx-utils/standardpath.h"
#include "fcitx-utils/stringutils.h"
#include "fcitx/addonfactory.h"
#include "fcitx/addonloader.h"
#include "fcitx/addonmanager.h"
#include "fcitx/instance.h"
#include "errorhandler.h"
#include <gtk/gtk.h>
#include <thread>

#ifdef ENABLE_KEYBOARD
#include "keyboard.h"
#endif

using namespace fcitx;
int selfpipe[2];
std::string crashlog;

#ifdef ENABLE_KEYBOARD
static KeyboardEngineFactory keyboardFactory;
#endif

StaticAddonRegistry staticAddon = {
#ifdef ENABLE_KEYBOARD
    std::make_pair<std::string, AddonFactory *>("keyboard", &keyboardFactory)
#endif
};


fcitx::StaticAddonRegistry staticAddons = {
    std::make_pair<std::string, fcitx::AddonFactory *>("keyboard",
                                                       &keyboardFactory)};

int main() {
    char arg0[] = "fcitx5";
    char arg1[] = "--disable=classicui";
    char *argv[] = {arg0, arg1};
    fcitx::Log::setLogRule("notimedate");
    auto instance_ = std::make_unique<fcitx::Instance>(FCITX_ARRAY_SIZE(argv), argv);
    auto &addonMgr = instance_->addonManager();
    addonMgr.registerDefaultLoader(&staticAddon);
    instance_->initialize();
    auto t = std::thread([&]() { instance_->exec(); });
    gtk_main();
    t.join();
}