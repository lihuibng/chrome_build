// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_MESSAGING_MESSAGING_DELEGATE_H_
#define CHROME_BROWSER_EXTENSIONS_API_MESSAGING_MESSAGING_DELEGATE_H_

#include <memory>
#include <string>

#include "base/callback_forward.h"
#include "base/macros.h"

class GURL;

namespace base {
class DictionaryValue;
}

namespace content {
class BrowserContext;
class WebContents;
}  // namespace content

namespace extensions {
class Extension;

// Helper class for Chrome-specific features of the extension messaging API.
// TODO(michaelpg): Make this an actual delegate and move the declaration to a
// common location.
class MessagingDelegate {
 public:
  enum class PolicyPermission {
    DISALLOW,           // The host is not allowed.
    ALLOW_SYSTEM_ONLY,  // Allowed only when installed on system level.
    ALLOW_ALL,          // Allowed when installed on system or user level.
  };

  // Checks whether native messaging is allowed for the given host.
  static PolicyPermission IsNativeMessagingHostAllowed(
      content::BrowserContext* browser_context,
      const std::string& native_host_name);

  // If web_contents is a tab, returns a dictionary representing its tab.
  // Otherwise returns nullptr.
  static std::unique_ptr<base::DictionaryValue> MaybeGetTabInfo(
      content::WebContents* web_contents);

  // Runs |callback| with true if |url| is allowed to connect to |extension|
  // from incognito mode, false otherwise. If the URL's origin has not been
  // granted/denied access yet, the user may be prompted before the callback is
  // run with their response.
  static void QueryIncognitoConnectability(
      content::BrowserContext* context,
      const Extension* extension,
      content::WebContents* web_contents,
      const GURL& url,
      const base::Callback<void(bool)>& callback);

 private:
  DISALLOW_COPY_AND_ASSIGN(MessagingDelegate);
};

}  // namespace extensions

#endif  // CHROME_BROWSER_EXTENSIONS_API_MESSAGING_MESSAGING_DELEGATE_H_