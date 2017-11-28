         mb.Printf("%%%c", token);
         do_quote = 0;
         break;
     }
 
     if (!p)
-        p = mb.buf;		/* do not use mb after this assignment! */
+        p = mb.buf;     /* do not use mb after this assignment! */
 
     assert(p);
 
     debugs(4, 3, "errorConvert: %%" << token << " --> '" << p << "'" );
 
     if (do_quote)
