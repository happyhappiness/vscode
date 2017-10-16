     " -q                 If used as the first parameter disables .curlrc",
     NULL
   };
   for(i=0; helptext[i]; i++) {
     puts(helptext[i]);
 #ifdef PRINT_LINES_PAUSE
-    if (i && ((i % PRINT_LINES_PAUSE) == 0))
+    if(i && ((i % PRINT_LINES_PAUSE) == 0))
       pressanykey();
 #endif
   }
 }
 
 struct LongShort {
