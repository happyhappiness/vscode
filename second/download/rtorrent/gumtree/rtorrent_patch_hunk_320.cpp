 //           3185 Skoppum, NORWAY
 
 #include "config.h"
 
 #include <stdexcept>
 #include <unistd.h>
-#include <rak/error_number.h>
+#include <torrent/exceptions.h>
+#include <torrent/poll_epoll.h>
+#include <torrent/poll_kqueue.h>
+#include <torrent/poll_select.h>
 
 #include "globals.h"
 #include "control.h"
 #include "manager.h"
 #include "poll_manager.h"
-#include "poll_manager_epoll.h"
-#include "poll_manager_kqueue.h"
-#include "poll_manager_select.h"
 
 namespace core {
 
-PollManager::PollManager(torrent::Poll* poll) :
-  m_poll(poll) {
-
-  if (m_poll == NULL)
-    throw std::logic_error("PollManager::PollManager(...) received poll == NULL");
-}
-
-PollManager::~PollManager() {
-  delete m_poll;
-}
-
-PollManager*
-PollManager::create_poll_manager() {
-  PollManager* pollManager = NULL;
-  Log* log = &control->core()->get_log_important();
-
-  const char* poll = getenv("RTORRENT_POLL");
+torrent::Poll*
+create_poll() {
+  const char* poll_name = getenv("RTORRENT_POLL");
 
   int maxOpen = sysconf(_SC_OPEN_MAX);
 
-  if (poll != NULL) {
-    if (!strcmp(poll, "epoll"))
-      pollManager = PollManagerEPoll::create(maxOpen);
-    else if (!strcmp(poll, "kqueue"))
-      pollManager = PollManagerKQueue::create(maxOpen);
-    else if (!strcmp(poll, "select"))
-      pollManager = PollManagerSelect::create(maxOpen);
+  torrent::Poll* poll = NULL;
+
+  if (poll_name != NULL) {
+    if (!strcmp(poll_name, "epoll"))
+      poll = torrent::PollEPoll::create(maxOpen);
+    else if (!strcmp(poll_name, "kqueue"))
+      poll = torrent::PollKQueue::create(maxOpen);
+    else if (!strcmp(poll_name, "select"))
+      poll = torrent::PollSelect::create(maxOpen);
 
-    if (pollManager == NULL)
-      log->push_front(std::string("Cannot enable '") + poll + "' based polling.");
+    if (poll == NULL)
+      control->core()->push_log_std(std::string("Cannot enable '") + poll_name + "' based polling.");
   }
 
-  if (pollManager != NULL)
-      log->push_front(std::string("Using '") + poll + "' based polling.");
+  if (poll != NULL)
+    control->core()->push_log_std(std::string("Using '") + poll_name + "' based polling.");
 
-  else if ((pollManager = PollManagerEPoll::create(maxOpen)) != NULL)
-    log->push_front("Using 'epoll' based polling.");
+  else if ((poll = torrent::PollEPoll::create(maxOpen)) != NULL)
+    control->core()->push_log_std("Using 'epoll' based polling.");
 
-  else if ((pollManager = PollManagerKQueue::create(maxOpen)) != NULL)
-    log->push_front("Using 'kqueue' based polling.");
+  else if ((poll = torrent::PollKQueue::create(maxOpen)) != NULL)
+    control->core()->push_log_std("Using 'kqueue' based polling.");
 
-  else if ((pollManager = PollManagerSelect::create(maxOpen)) != NULL)
-    log->push_front("Using 'select' based polling.");
+  else if ((poll = torrent::PollSelect::create(maxOpen)) != NULL)
+    control->core()->push_log_std("Using 'select' based polling.");
 
   else
-    throw std::runtime_error("Could not create any PollManager.");
-
-  return pollManager;
-}
+    throw torrent::internal_error("Could not create any Poll object.");
 
-void
-PollManager::check_error() {
-  if (rak::error_number::current().value() != rak::error_number::e_intr)
-    throw std::runtime_error("Poll::work(): " + std::string(rak::error_number::current().c_str()));
+  return poll;
 }
 
 }
