   m_canvas->erase();
 
   int pos = 0;
 
   m_canvas->print( 2, pos, "File");
   m_canvas->print(55, pos, "Size");
-  m_canvas->print(62, pos, "Pri");
-  m_canvas->print(67, pos, "Cmpl");
+  m_canvas->print(63, pos, "Pri");
+  m_canvas->print(68, pos, "Cmpl");
 
   ++pos;
 
   if (m_download->get_download().get_entry_size() == 0)
     return;
 
