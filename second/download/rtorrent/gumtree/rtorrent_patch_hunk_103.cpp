 WindowStatusbar::redraw() {
   m_slotSchedule(this, (cachedTime + 1000000).round_seconds());
 
   m_canvas->erase();
 
   // TODO: Make a buffer with size = get_width?
-  int pos = 0;
-  char buf[128];
+  char buffer[m_canvas->get_width() + 1];
+  char* position;
+  char* last = buffer + m_canvas->get_width();
+
+//   if (torrent::up_throttle() == 0)
+//     position = std::max(snprintf(buffer, 128, "off/"), 0);
+//   else
+//     position = std::max(snprintf(buffer, 128, "%3i/", torrent::up_throttle() / 1024), 0);
+
+//   if (torrent::down_throttle() == 0)
+//     pos = snprintf(buf + pos, 128 - pos, "off");
+//   else
+//     pos = snprintf(buf + pos, 128 - pos, "%-3i", torrent::down_throttle() / 1024);
+
+//   m_canvas->print(0, 0, "Throttle U/D: %s  Rate: %5.1f / %5.1f KB  Listen: %s:%i%s",
+// 		  buf,
+// 		  (double)torrent::up_rate()->rate() / 1024.0,
+// 		  (double)torrent::down_rate()->rate() / 1024.0,
+// 		  !torrent::local_address().empty() ? torrent::local_address().c_str() : "<default>",
+// 		  (int)torrent::listen_port(),
+// 		  !torrent::bind_address().empty() ? ("  Bind: " + torrent::bind_address()).c_str() : "");
+
+// #ifndef USE_EXTRA_DEBUG
+//   pos = snprintf(buf, 128, "[U %i/%i][S %i/%i/%i][F %i/%i]",
+// #else
+//   pos = snprintf(buf, 128, "%i [U %i/%i][S %i/%i/%i][F %i/%i]",
+// 		 (int)(m_control->tick() - m_lastTick),
+// #endif
+// 		 torrent::currently_unchoked(),
+// 		 torrent::max_unchoked(),
+// 		 torrent::total_handshakes(),
+// 		 torrent::open_sockets(),
+// 		 torrent::max_open_sockets(),
+// 		 torrent::open_files(),
+// 		 torrent::max_open_files());
+
+  position = print_status_info(buffer, last);
+  m_canvas->print(0, 0, "%s", buffer);
+
+  last = last - (position - buffer);
+
+  if (last > buffer) {
+    position = print_status_extra(buffer, last, m_control);
+    m_canvas->print(m_canvas->get_width() - (position - buffer), 0, "%s", buffer);
+  }
 
-  if (torrent::up_throttle() == 0)
-    pos = snprintf(buf, 128, "off/");
-  else
-    pos = snprintf(buf, 128, "%3i/", torrent::up_throttle() / 1024);
-
-  if (torrent::down_throttle() == 0)
-    pos = snprintf(buf + pos, 128 - pos, "off");
-  else
-    pos = snprintf(buf + pos, 128 - pos, "%-3i", torrent::down_throttle() / 1024);
-
-  m_canvas->print(0, 0, "Throttle U/D: %s  Rate: %5.1f / %5.1f KB  Listen: %s:%i%s",
-		  buf,
-		  (double)torrent::up_rate()->rate() / 1024.0,
-		  (double)torrent::down_rate()->rate() / 1024.0,
-		  !torrent::local_address().empty() ? torrent::local_address().c_str() : "<default>",
-		  (int)torrent::listen_port(),
-		  !torrent::bind_address().empty() ? ("  Bind: " + torrent::bind_address()).c_str() : "");
-
-#ifndef USE_EXTRA_DEBUG
-  pos = snprintf(buf, 128, "[U %i/%i][S %i/%i/%i][F %i/%i]",
-#else
-  pos = snprintf(buf, 128, "%i [U %i/%i][S %i/%i/%i][F %i/%i]",
-		 (int)(m_control->tick() - m_lastTick),
-#endif
-		 torrent::currently_unchoked(),
-		 torrent::max_unchoked(),
-		 torrent::total_handshakes(),
-		 torrent::open_sockets(),
-		 torrent::max_open_sockets(),
-		 torrent::open_files(),
-		 torrent::max_open_files());
-
-  m_canvas->print(m_canvas->get_width() - pos, 0, "%s", buf);
 
   m_lastTick = m_control->tick();
 }
 
 }
