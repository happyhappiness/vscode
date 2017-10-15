 
     default:
       priority = "BUG";
       break;
     };
 
-    m_canvas->print(0, pos, "%c %s  %5.1f   %s   %3d",
+    m_canvas->print(0, pos, "%c %s  %6.1f   %s   %3d",
 		    range.first == *m_focus ? '*' : ' ',
 		    path.c_str(),
 		    (double)e.get_size() / (double)(1 << 20),
 		    priority.c_str(),
 		    done_percentage(e));
 
