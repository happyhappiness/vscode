   position = print_status_info(buffer, last);
   m_canvas->print(0, 0, "%s", buffer);
 
   last = last - (position - buffer);
 
   if (last > buffer) {
-    position = print_status_extra(buffer, last, control);
+    position = print_status_extra(buffer, last);
     m_canvas->print(m_canvas->width() - (position - buffer), 0, "%s", buffer);
   }
 
   m_lastTick = control->tick();
 }
 
