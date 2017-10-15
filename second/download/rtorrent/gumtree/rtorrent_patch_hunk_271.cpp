       itr.backward_current_depth();
     else
       --itr;
   }
 
   unsigned int pos = 0;
+  int filenameWidth = m_canvas->width() - 16;
+
   m_canvas->print(0, pos++, "Cmp Pri  Size   Filename");
 
   while (pos != m_canvas->height()) {
     iterator itr = entries[first];
 
     if (itr == iterator(fl->end()))
       break;
 
+    m_canvas->set_default_attributes(itr == m_element->selected() ? is_focused() ? A_REVERSE : A_BOLD : A_NORMAL);
+
     if (itr.is_empty()) {
-      m_canvas->print(16, pos, "EMPTY");
+      m_canvas->print(0, pos, "%*c%-*s", 16, ' ', filenameWidth, "EMPTY");
 
     } else if (itr.is_entering()) {
-      m_canvas->print(16 + itr.depth(), pos, "\\ %s", 
-                      itr.depth() < (*itr)->path()->size() ? (*itr)->path()->at(itr.depth()).c_str() : "UNKNOWN");
+      m_canvas->print(0, pos, "%*c %ls", 16 + itr.depth(), '\\',
+                      itr.depth() < (*itr)->path()->size() ? wstring_width((*itr)->path()->at(itr.depth()), filenameWidth - itr.depth() - 1).c_str() : L"UNKNOWN");
 
     } else if (itr.is_leaving()) {
-      m_canvas->print(16 + itr.depth() - 1, pos, "/");
+      m_canvas->print(0, pos, "%*c %-*s", 16 + (itr.depth() - 1), '/', filenameWidth - (itr.depth() - 1), "");
 
     } else if (itr.is_file()) {
-      char buffer[std::max<unsigned int>(m_canvas->width() + 1, 256)];
-      Canvas::attributes_list attributes;
-
       torrent::File* e = *itr;
 
       const char* priority;
 
       switch (e->priority()) {
       case torrent::PRIORITY_OFF:    priority = "off"; break;
       case torrent::PRIORITY_NORMAL: priority = "   "; break;
       case torrent::PRIORITY_HIGH:   priority = "hig"; break;
       default: priority = "BUG"; break;
       };
 
-      sprintf(buffer, "%3d %s ", done_percentage(e), priority);
+      m_canvas->print(0, pos, "%3d %s ", done_percentage(e), priority);
 
       int64_t val = e->size_bytes();
 
-      if (val < (int64_t(1000) << 20))
-        sprintf(buffer + 8, "%5.1f M", (double)val / (int64_t(1) << 20));
+      if (val < (int64_t(1000) << 10))
+        m_canvas->print(8, pos, "%5.1f K", (double)val / (int64_t(1) << 10));
+      else if (val < (int64_t(1000) << 20))
+        m_canvas->print(8, pos, "%5.1f M", (double)val / (int64_t(1) << 20));
       else if (val < (int64_t(1000) << 30))
-        sprintf(buffer + 8, "%5.1f G", (double)val / (int64_t(1) << 30));
+        m_canvas->print(8, pos, "%5.1f G", (double)val / (int64_t(1) << 30));
       else
-        sprintf(buffer + 8, "%5.1f T", (double)val / (int64_t(1) << 40));
+        m_canvas->print(8, pos, "%5.1f T", (double)val / (int64_t(1) << 40));
 
-      std::fill_n(buffer + 15, 64, ' ');
-
-      int first = 16 + std::min<unsigned int>(itr.depth(), 8);
-      int last = std::max<unsigned int>(m_canvas->width() + 1, 16 + 12);
-
-      snprintf(buffer + first, last - first, "| %s",
-               itr.depth() < (*itr)->path()->size() ? (*itr)->path()->at(itr.depth()).c_str() : "UNKNOWN");
-
-      m_canvas->print_attributes(0, pos, buffer, buffer + std::strlen(buffer), &attributes);
+      m_canvas->print(15, pos, "%*c %ls", 1 + itr.depth(), '|',
+                      itr.depth() < (*itr)->path()->size() ? wstring_width((*itr)->path()->at(itr.depth()), filenameWidth - itr.depth() - 1).c_str() : L"UNKNOWN");
 
     } else {
       m_canvas->print(0, pos, "BORK BORK");
     }
-
-    if (itr == m_element->selected())
-      m_canvas->set_attr(0, pos, m_canvas->width(), is_focused() ? A_REVERSE : A_BOLD, COLOR_PAIR(0));
+    m_canvas->set_default_attributes(A_NORMAL);
 
     pos++;
     first = (first + 1) % (m_canvas->height() - 1);
   }
 }
 
