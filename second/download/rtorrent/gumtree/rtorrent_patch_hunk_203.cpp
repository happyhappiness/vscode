 //                       e->match_depth_next());
 
     } else {
       m_canvas->print(0, pos, "BORK BORK");
     }
 
-    if (itr == *m_selected)
+    if (itr == m_element->selected())
       m_canvas->set_attr(0, pos, m_canvas->width(), is_focused() ? A_REVERSE : A_BOLD, COLOR_PAIR(0));
 
-    ++itr;
-    ++pos;
+    pos++;
+    first = (first + 1) % (m_canvas->height() - 1);
   }
 }
 
 int
 WindowFileList::done_percentage(torrent::File* e) {
   int chunks = e->range().second - e->range().first;
