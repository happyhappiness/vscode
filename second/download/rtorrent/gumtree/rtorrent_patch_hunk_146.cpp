   m_canvas->print(x, y, "DOWN");    x += 7;
   m_canvas->print(x, y, "PEER");    x += 7;
   m_canvas->print(x, y, "C/RE/LO"); x += 9;
   m_canvas->print(x, y, "QS");      x += 6;
   m_canvas->print(x, y, "DONE");    x += 6;
   m_canvas->print(x, y, "REQ");     x += 6;
-  m_canvas->print(x, y, "SNUB");
+  m_canvas->print(x, y, "SNUB");    x += 6;
+  m_canvas->print(x, y, "FAILED");
 
   ++y;
 
   if (m_list->empty())
     return;
 
