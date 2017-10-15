   // TODO: Make this depend on tracker signal.
   m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(10)).round_seconds());
   m_canvas->erase();
 
   unsigned int pos = 0;
   torrent::TrackerList* tl = m_download->tracker_list();
+  torrent::TrackerController* tc = m_download->tracker_controller();
 
-  m_canvas->print(2, pos, "Trackers: [Key: %08x]", tl->key());
+  m_canvas->print(2, pos, "Trackers: [Key: %08x] [%s %s %s]",
+                  tl->key(),
+                  tc->is_requesting() ? "req" : "   ",
+                  tc->is_promiscuous_mode() ? "prom" : "    ",
+                  tc->is_failure_mode() ? "fail" : "    ");
   ++pos;
 
   if (tl->size() == 0 || *m_focus >= tl->size())
     return;
 
   typedef std::pair<unsigned int, unsigned int> Range;
