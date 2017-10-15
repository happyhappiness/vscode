       break;
     };
 
     m_canvas->print(0, pos, "%c %s  %6.1f   %s   %3d  %9s",
                     range.first == *m_focus ? '*' : ' ',
                     path.c_str(),
-                    (double)e.size_bytes() / (double)(1 << 20),
+                    (double)e->size_bytes() / (double)(1 << 20),
                     priority.c_str(),
                     done_percentage(e),
-                    e.path()->encoding().c_str());
+                    e->path()->encoding().c_str());
 
     m_canvas->print(84, pos, "%i - %i %c%c",
-                    e.chunk_begin(),
-                    e.chunk_begin() != e.chunk_end() ? (e.chunk_end() - 1) : e.chunk_end(),
-                    e.is_created() ? 'E' : 'M',
-                    e.is_correct_size() ? 'C' : 'W');
+                    e->range().first,
+                    e->range().first != e->range().second ? (e->range().second - 1) : e->range().second,
+                    e->is_created() ? 'E' : 'M',
+                    e->is_correct_size() ? 'C' : 'W');
 
     ++range.first;
     ++pos;
   }
 
 }
 
 int
-WindowFileList::done_percentage(torrent::File& e) {
-  int chunks = e.chunk_end() - e.chunk_begin();
+WindowFileList::done_percentage(torrent::File* e) {
+  int chunks = e->range().second - e->range().first;
 
-  return chunks ? (e.completed_chunks() * 100) / chunks : 100;
+  return chunks ? (e->completed_chunks() * 100) / chunks : 100;
 }
 
 }
