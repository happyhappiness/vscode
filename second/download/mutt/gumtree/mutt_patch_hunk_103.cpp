 {
   int c, linelen = 0;
   char line[77], savechar;
 
   while ((c = fgetconv (fc)) != EOF)
   {
-    /* Escape lines that begin with "the message separator". */
-    if (linelen == 5 && !mutt_strncmp ("From ", line, 5))
-    {
-      strfcpy (line, "=46rom ", sizeof (line));
-      linelen = 7;
-    }
-    else if (linelen == 1 && line[0] == '.')
-    {
-      strfcpy (line, "=2E", sizeof (line));
-      linelen = 3;
-    }
-
     /* Wrap the line if needed. */
     if (linelen == 76 && ((istext && c != '\n') || !istext))
     {
       /* If the last character is "quoted", then be sure to move all three
        * characters to the next line.  Otherwise, just move the last
        * character...
        */
       if (line[linelen-3] == '=')
       {
         line[linelen-3] = 0;
-        fputs (line, fout);      
+        fputs (line, fout);
         fputs ("=\n", fout);
         line[linelen] = 0;
         line[0] = '=';
         line[1] = line[linelen-2];
         line[2] = line[linelen-1];
         linelen = 3;
