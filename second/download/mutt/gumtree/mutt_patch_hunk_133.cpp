   int split;
   int n;
 
   fputs (t1, f);
 
   /* don't try to press string into one line with less than 40 characters.
-     The double paranthesis avoid a gcc warning, sigh ... */
+     The double parenthesis avoids a gcc warning, sigh ... */
   if ((split = COLS < 40))
   {
     col_a = col = 0;
     col_b = LONG_STRING;
     fputc ('\n', f);
   }
