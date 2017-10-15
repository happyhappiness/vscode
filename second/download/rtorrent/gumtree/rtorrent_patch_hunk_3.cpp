     last = m_list->end();
   }    
 
   while (itr != m_list->end() && y < m_canvas->get_height()) {
     m_canvas->print(0, pos++, "%c %s",
 		    itr == *m_focus ? '*' : ' ',
-		    itr->get_download().get_name().c_str());
+		    (*itr)->get_download().get_name().c_str());
 
-    if (itr->get_download().get_chunks_done() != itr->get_download().get_chunks_total() || !itr->get_download().is_open())
+    if ((*itr)->get_download().get_chunks_done() != (*itr)->get_download().get_chunks_total() || !(*itr)->get_download().is_open())
       m_canvas->print(0, pos++, "%c Torrent: %.1f / %.1f MiB Rate:%5.1f /%5.1f KiB Uploaded: %.1f MiB",
 		      itr == *m_focus ? '*' : ' ',
-		      (double)itr->get_download().get_bytes_done() / (double)(1 << 20),
-		      (double)itr->get_download().get_bytes_total() / (double)(1 << 20),
-		      (double)itr->get_download().get_rate_up() / 1024.0,
-		      (double)itr->get_download().get_rate_down() / 1024.0,
-		      (double)itr->get_download().get_bytes_up() / (double)(1 << 20));
+		      (double)(*itr)->get_download().get_bytes_done() / (double)(1 << 20),
+		      (double)(*itr)->get_download().get_bytes_total() / (double)(1 << 20),
+		      (double)(*itr)->get_download().get_rate_up() / 1024.0,
+		      (double)(*itr)->get_download().get_rate_down() / 1024.0,
+		      (double)(*itr)->get_download().get_bytes_up() / (double)(1 << 20));
  
     else
       m_canvas->print(0, pos++, "%c Torrent: Done %.1f MiB Rate:%5.1f /%5.1f KiB Uploaded: %.1f MiB",
 		      itr == *m_focus ? '*' : ' ',
-		      (double)itr->get_download().get_bytes_total() / (double)(1 << 20),
-		      (double)itr->get_download().get_rate_up() / 1024.0,
-		      (double)itr->get_download().get_rate_down() / 1024.0,
-		      (double)itr->get_download().get_bytes_up() / (double)(1 << 20));
+		      (double)(*itr)->get_download().get_bytes_total() / (double)(1 << 20),
+		      (double)(*itr)->get_download().get_rate_up() / 1024.0,
+		      (double)(*itr)->get_download().get_rate_down() / 1024.0,
+		      (double)(*itr)->get_download().get_bytes_up() / (double)(1 << 20));
     
-    m_canvas->print(0, pos++, "%c %s", itr == *m_focus ? '*' : ' ', print_download_status(&*itr).c_str());
+    m_canvas->print(0, pos++, "%c %s", itr == *m_focus ? '*' : ' ', print_download_status(*itr).c_str());
 
     ++itr;
   }    
 }
 
 }
