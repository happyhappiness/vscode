   if (range.second != m_list->end())
     ++range.second;
 
   int pos = 0;
 
   while (range.first != range.second) {
-    torrent::Download& d = (*range.first)->get_download();
+    char buffer[m_canvas->get_width() - 2];
+    char* position;
+    char* last = buffer + m_canvas->get_width() - 2;
 
-    m_canvas->print(0, pos++, "%c %s",
-		    range.first == m_list->get_focus() ? '*' : ' ',
-		    d.get_name().c_str());
-
-    if ((*range.first)->is_open() && (*range.first)->is_done())
-      m_canvas->print(0, pos++, "%c Torrent: Done %10.1f MiB Rate: %5.1f / %5.1f KiB Uploaded: %.1f MiB",
-		      range.first == m_list->get_focus() ? '*' : ' ',
-		      (double)d.get_bytes_total() / (double)(1 << 20),
-		      (double)d.get_rate_up() / 1024.0,
-		      (double)d.get_rate_down() / 1024.0,
-		      (double)d.get_bytes_up() / (double)(1 << 20));
-    else
-      m_canvas->print(0, pos++, "%c Torrent: %6.1f / %6.1f MiB Rate: %5.1f / %5.1f KiB Uploaded: %.1f MiB",
-		      range.first == m_list->get_focus() ? '*' : ' ',
-		      (double)d.get_bytes_done() / (double)(1 << 20),
-		      (double)d.get_bytes_total() / (double)(1 << 20),
-		      (double)d.get_rate_up() / 1024.0,
-		      (double)d.get_rate_down() / 1024.0,
-		      (double)d.get_bytes_up() / (double)(1 << 20));
+    position = print_download_title(buffer, last - buffer, *range.first);
+    m_canvas->print(0, pos++, "%c %s", range.first == m_list->get_focus() ? '*' : ' ', buffer);
     
-    m_canvas->print(0, pos++, "%c %s",
-		    range.first == m_list->get_focus() ? '*' : ' ',
-		    print_download_status(*range.first).c_str());
+    position = print_download_info(buffer, last - buffer, *range.first);
+    m_canvas->print(0, pos++, "%c %s", range.first == m_list->get_focus() ? '*' : ' ', buffer);
+
+    position = print_download_status(buffer, last - buffer, *range.first);
+    m_canvas->print(0, pos++, "%c %s", range.first == m_list->get_focus() ? '*' : ' ', buffer);
 
     ++range.first;
   }    
 }
 
 }
