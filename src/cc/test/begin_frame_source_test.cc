// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "cc/test/begin_frame_source_test.h"

#include "components/viz/test/begin_frame_args_test.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace cc {

void MockBeginFrameObserver::AsValueInto(
    base::trace_event::TracedValue* dict) const {
  dict->SetString("type", "MockBeginFrameObserver");
  dict->BeginDictionary("last_begin_frame_args");
  last_begin_frame_args.AsValueInto(dict);
  dict->EndDictionary();
}

MockBeginFrameObserver::MockBeginFrameObserver()
    : last_begin_frame_args(kDefaultBeginFrameArgs) {
  ON_CALL(*this, LastUsedBeginFrameArgs())
      .WillByDefault(::testing::ReturnPointee(&last_begin_frame_args));
}

MockBeginFrameObserver::~MockBeginFrameObserver() {}

const viz::BeginFrameArgs MockBeginFrameObserver::kDefaultBeginFrameArgs =
    viz::CreateBeginFrameArgsForTesting(
#ifdef NDEBUG
        nullptr,
#else
        FROM_HERE_WITH_EXPLICIT_FUNCTION(
            "MockBeginFrameObserver::kDefaultBeginFrameArgs"),
#endif
        viz::BeginFrameArgs::kManualSourceId,
        viz::BeginFrameArgs::kStartingFrameNumber,
        -1,
        -1,
        -1);

}  // namespace cc