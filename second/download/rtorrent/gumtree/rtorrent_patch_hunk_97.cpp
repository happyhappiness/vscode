 
 #include "config.h"
 
 #include <cstring>
 #include <sstream>
 #include <iomanip>
+#include <torrent/exceptions.h>
 #include <torrent/rate.h>
 #include <torrent/tracker.h>
 
 #include "core/download.h"
 #include <rak/timer.h>
 
 #include "utils.h"
 
 namespace display {
 
+inline char*
+print_buffer(char* first, char* last, const char* format) {
+  if (first >= last)
+    return first;
+
+  int s = snprintf(first, last - first, format);
+
+  if (s < 0)
+    return first;
+  else
+    return std::min(first + s, last);
+}
+
+template <typename Arg1>
+inline char*
+print_buffer(char* first, char* last, const char* format, const Arg1& arg1) {
+  if (first >= last)
+    return first;
+
+  int s = snprintf(first, last - first, format, arg1);
+
+  if (s < 0)
+    return first;
+  else
+    return std::min(first + s, last);
+}
+
+template <typename Arg1, typename Arg2>
+inline char*
+print_buffer(char* first, char* last, const char* format, const Arg1& arg1, const Arg2& arg2) {
+  if (first >= last)
+    return first;
+
+  int s = snprintf(first, last - first, format, arg1, arg2);
+
+  if (s < 0)
+    return first;
+  else
+    return std::min(first + s, last);
+}
+
+template <typename Arg1, typename Arg2, typename Arg3>
+inline char*
+print_buffer(char* first, char* last, const char* format, const Arg1& arg1, const Arg2& arg2, const Arg3& arg3) {
+  if (first >= last)
+    return first;
+
+  int s = snprintf(first, last - first, format, arg1, arg2, arg3);
+
+  if (s < 0)
+    return first;
+  else
+    return std::min(first + s, last);
+}
+
 char*
-print_string(char* buf, unsigned int length, char* str) {
+print_string(char* first, char* last, char* str) {
   // We don't have any nice simple functions for copying strings that
   // return the end address.
-  while (length-- != 0 && *str != '\0')
-    *(buf++) = *(str++);
+  while (first != last && *str != '\0')
+    *(first++) = *(str++);
 
-  return buf;
+  return first;
 }
 
 char*
-print_hhmmss(char* buf, unsigned int length, time_t t) {
+print_hhmmss(char* first, char* last, time_t t) {
   std::tm *u = std::localtime(&t);
   
   if (u == NULL)
-    return "inv_time";
-
-  int s = snprintf(buf, length, "%2u:%02u:%02u", u->tm_hour, u->tm_min, u->tm_sec);
+    //return "inv_time";
+    throw torrent::internal_error("print_hhmmss(...) failed.");
 
-  return buf + std::max(s, 0);
+  return print_buffer(first, last, "%2u:%02u:%02u", u->tm_hour, u->tm_min, u->tm_sec);
 }
 
 char*
-print_ddhhmm(char* buf, unsigned int length, time_t t) {
-  int s;
-
+print_ddhhmm(char* first, char* last, time_t t) {
   if (t / (24 * 3600) < 100)
-    s = snprintf(buf, length, "%2i:%02i:%02i", (int)t / (24 * 3600), ((int)t / 3600) % 24, ((int)t / 60) % 60);
+    return print_buffer(first, last, "%2i:%02i:%02i", (int)t / (24 * 3600), ((int)t / 3600) % 24, ((int)t / 60) % 60);
   else
-    s = snprintf(buf, length, "--:--:--");
-  
-  return buf + std::max(s, 0);
+    return print_buffer(first, last, "--:--:--");
 }
 
 char*
-print_ddmmyyyy(char* buf, unsigned int length, time_t t) {
+print_ddmmyyyy(char* first, char* last, time_t t) {
   std::tm *u = std::gmtime(&t);
   
   if (u == NULL)
-    return "inv_time";
-
-  int s = snprintf(buf, length, "%02u/%02u/%04u", u->tm_mday, (u->tm_mon + 1), (1900 + u->tm_year));
+    //return "inv_time";
+    throw torrent::internal_error("print_ddmmyyyy(...) failed.");
 
-  return buf + std::max(s, 0);
+  return print_buffer(first, last, "%02u/%02u/%04u", u->tm_mday, (u->tm_mon + 1), (1900 + u->tm_year));
 }
 
 char*
-print_download_title(char* buf, unsigned int length, core::Download* d) {
-  return buf + std::max(snprintf(buf, length, "%s", d->get_download().name().c_str()), 0);
+print_download_title(char* first, char* last, core::Download* d) {
+  return print_buffer(first, last, "%s", d->get_download().name().c_str());
 }
 
 char*
-print_download_info(char* buf, unsigned int length, core::Download* d) {
-  char* last = buf + length;
-
-  buf += std::max(snprintf(buf, last - buf, "Torrent: "), 0);
+print_download_info(char* first, char* last, core::Download* d) {
+  first = print_buffer(first, last, "Torrent: ");
 
   if (!d->get_download().is_open())
-    buf += std::max(snprintf(buf, last - buf, "closed            "), 0);
+    first = print_buffer(first, last, "closed            ");
+
   else if (d->is_done())
-    buf += std::max(snprintf(buf, last - buf, "done %10.1f MB",
-			     (double)d->get_download().bytes_total() / (double)(1 << 20)), 0);
+    first = print_buffer(first, last, "done %10.1f MB", (double)d->get_download().bytes_total() / (double)(1 << 20));
   else
-    buf += std::max(snprintf(buf, last - buf, "%6.1f / %6.1f MB",
-			     (double)d->get_download().bytes_done() / (double)(1 << 20),
-			     (double)d->get_download().bytes_total() / (double)(1 << 20)), 0);
-  
-  buf += std::max(snprintf(buf, last - buf, " Rate: %5.1f / %5.1f KB Uploaded: %7.1f MB ",
-			   (double)d->get_download().up_rate()->rate() / (1 << 10),
-			   (double)d->get_download().down_rate()->rate() / (1 << 10),
-			   (double)d->get_download().up_rate()->total() / (1 << 20)), 0);
+    first = print_buffer(first, last, "%6.1f / %6.1f MB",
+		       (double)d->get_download().bytes_done() / (double)(1 << 20),
+		       (double)d->get_download().bytes_total() / (double)(1 << 20));
+  
+  first = print_buffer(first, last, " Rate: %5.1f / %5.1f KB Uploaded: %7.1f MB",
+		     (double)d->get_download().up_rate()->rate() / (1 << 10),
+		     (double)d->get_download().down_rate()->rate() / (1 << 10),
+		     (double)d->get_download().up_rate()->total() / (1 << 20));
+
+  if (d->get_download().is_active() && !d->is_done()) {
+    first = print_buffer(first, last, " ");
+    first = print_download_percentage_done(first, last, d);
+
+    first = print_buffer(first, last, " ");
+    first = print_download_time_left(first, last, d);
+  } else {
+    first = print_buffer(first, last, "               ");
+  }
+
+  if (d->priority() != 2)
+    first = print_buffer(first, last, " [%s]", core::Download::priority_to_string(d->priority()));
 
-  buf = print_download_time_left(buf, last - buf, d);
+  if (first > last)
+    throw torrent::internal_error("print_download_info(...) wrote past end of the buffer.");
 
-  return buf;
+  return first;
 }
 
 char*
-print_download_status(char* buf, unsigned int length, core::Download* d) {
-  char* last = buf + length;
-
+print_download_status(char* first, char* last, core::Download* d) {
   if (!d->get_download().is_active())
-    buf += std::max(snprintf(buf, last - buf, "Inactive: "), 0);
+    first = print_buffer(first, last, "Inactive: ");
 
   if (d->get_download().is_hash_checking())
-    buf += std::max(snprintf(buf, last - buf, "Checking hash [%2i%%]",
-			     (d->get_download().chunks_hashed() * 100) / d->get_download().chunks_total()), 0);
+    first = print_buffer(first, last, "Checking hash [%2i%%]",
+		       (d->get_download().chunks_hashed() * 100) / d->get_download().chunks_total());
 
   else if (d->get_download().is_tracker_busy() &&
 	   d->get_download().tracker_focus() < d->get_download().size_trackers())
-    buf += std::max(snprintf(buf, last - buf, "Tracker[%i:%i]: Connecting to %s",
-			     d->get_download().tracker(d->get_download().tracker_focus()).group(),
-			     d->get_download().tracker_focus(),
-			     d->get_download().tracker(d->get_download().tracker_focus()).url().c_str()), 0);
+    first = print_buffer(first, last, "Tracker[%i:%i]: Connecting to %s",
+		       d->get_download().tracker(d->get_download().tracker_focus()).group(),
+		       d->get_download().tracker_focus(),
+		       d->get_download().tracker(d->get_download().tracker_focus()).url().c_str());
 
   else if (!d->get_message().empty())
-    buf += std::max(snprintf(buf, last - buf, "%s", d->get_message().c_str()), 0);
+    first = print_buffer(first, last, "%s", d->get_message().c_str());
 
   else
-    buf[0] = '\0';
+    *first = '\0';
+
+  if (first > last)
+    throw torrent::internal_error("print_download_status(...) wrote past end of the buffer.");
 
-  return buf;
+  return first;
 }
 
 char*
-print_download_time_left(char* buf, unsigned int length, core::Download* d) {
-  uint32_t rate;
+print_download_time_left(char* first, char* last, core::Download* d) {
+  uint32_t rate = d->get_download().down_rate()->rate();
 
-  if (!d->get_download().is_active() ||
-      (rate = d->get_download().down_rate()->rate()) < 512) {
-    buf += std::max(0, snprintf(buf, length, "--:--:--"));
-    return buf;
-  }
+  if (rate < 512)
+    return print_buffer(first, last, "--:--:--");
   
   time_t remaining = (d->get_download().bytes_total() - d->get_download().bytes_done()) / (rate & ~(uint32_t)(512 - 1));
 
-  return print_ddhhmm(buf, length, remaining);
+  return print_ddhhmm(first, last, remaining);
 }
 
-// char*
-// print_entry_tags(char* buf, unsigned int length) {
+char*
+print_download_percentage_done(char* first, char* last, core::Download* d) {
+  if (!d->is_open() || d->is_done())
+    //return print_buffer(first, last, "[--%%]");
+    return print_buffer(first, last, "     ");
+  else
+    return print_buffer(first, last, "[%2u%%]", (d->get_download().chunks_done() * 100) / d->get_download().chunks_total());
+}
+
+char*
+print_status_info(char* first, char* last) {
+  if (torrent::up_throttle() == 0)
+    first = print_buffer(first, last, "[Throttle off");
+  else
+    first = print_buffer(first, last, "[Throttle %3i", torrent::up_throttle() / 1024);
+
+  if (torrent::down_throttle() == 0)
+    first = print_buffer(first, last, "/off KB]");
+  else
+    first = print_buffer(first, last, "/%3i KB]", torrent::down_throttle() / 1024);
+  
+  first = print_buffer(first, last, " [Rate %5.1f/%5.1f KB]",
+		       (double)torrent::up_rate()->rate() / 1024.0,
+		       (double)torrent::down_rate()->rate() / 1024.0);
+
+  first = print_buffer(first, last, " [Listen %s:%u]",
+		       torrent::local_address().c_str(),
+		       (unsigned int)torrent::listen_port());
   
-// }
+  if (first > last)
+    throw torrent::internal_error("print_status_info(...) wrote past end of the buffer.");
+
+  std::string bindAddress = torrent::bind_address();
+
+  if (!bindAddress.empty())
+    first = print_buffer(first, last, " [Bind %s]", bindAddress.c_str());
 
-// char*
-// print_entry_file(char* buf, unsigned int length, const torrent::Entry& entry);
+  return first;
+}
+
+char*
+print_status_extra(char* first, char* last, Control* c) {
+  first = print_buffer(first, last, " [U %i/%i]",
+		       torrent::currently_unchoked(),
+		       torrent::max_unchoked());
+
+  first = print_buffer(first, last, " [S %i/%i/%i]",
+		       torrent::total_handshakes(),
+		       torrent::open_sockets(),
+		       torrent::max_open_sockets());
+		       
+  first = print_buffer(first, last, " [F %i/%i]",
+		       torrent::open_files(),
+		       torrent::max_open_files());
+
+  return first;
+}
 
 }
