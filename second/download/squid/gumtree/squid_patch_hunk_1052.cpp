 
     case '%':
         p = "%";
         break;
 
     default:
-        mb.Printf("%%%c", token);
+        mb.appendf("%%%c", token);
         do_quote = 0;
         break;
     }
 
     if (!p)
         p = mb.buf;     /* do not use mb after this assignment! */
