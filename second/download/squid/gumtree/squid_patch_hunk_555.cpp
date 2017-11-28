         m = p + 1;			/* advance */
     }
 
     if (*m)
         content->Printf("%s", m);	/* copy tail */
 
+    content->terminate();
+
     assert((size_t)content->contentSize() == strlen(content->content()));
 
     return content;
 }
