 		    priority.c_str(),
 		    done_percentage(e),
 		    e.path()->encoding().c_str());
 
     m_canvas->print(84, pos, "%i - %i",
 		    e.chunk_begin(),
-		    e.chunk_end());
+		    e.chunk_begin() != e.chunk_end() ? (e.chunk_end() - 1) : e.chunk_end());
 
     ++range.first;
     ++pos;
   }
 
 }
