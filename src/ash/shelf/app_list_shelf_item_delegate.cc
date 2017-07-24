// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/shelf/app_list_shelf_item_delegate.h"

#include <utility>

#include "ash/public/cpp/shelf_model.h"
#include "ash/shell.h"

namespace ash {

AppListShelfItemDelegate::AppListShelfItemDelegate()
    : ShelfItemDelegate(ShelfID(kAppListId)) {}

AppListShelfItemDelegate::~AppListShelfItemDelegate() {}

void AppListShelfItemDelegate::ItemSelected(std::unique_ptr<ui::Event> event,
                                            int64_t display_id,
                                            ShelfLaunchSource source,
                                            ItemSelectedCallback callback) {
  Shell::Get()->ToggleAppList();
  std::move(callback).Run(SHELF_ACTION_APP_LIST_SHOWN, base::nullopt);
}

void AppListShelfItemDelegate::ExecuteCommand(uint32_t command_id,
                                              int32_t event_flags) {
  // This delegate does not support showing an application menu.
  NOTIMPLEMENTED();
}

void AppListShelfItemDelegate::Close() {}

}  // namespace ash