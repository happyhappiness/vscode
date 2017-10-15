   fputc('\n', fout);
 }
 
 static void encode_8bit (FGETCONV *fc, FILE *fout, int istext)
 {
   int ch;
-  
+
   while ((ch = fgetconv (fc)) != EOF)
     fputc (ch, fout);
 }
-  
+
 
 int mutt_write_mime_header (BODY *a, FILE *f)
 {
   PARAMETER *p;
   char buffer[STRING];
   char *t;
   char *fn;
   int len;
   int tmplen;
   int encode;
-  
+
   fprintf (f, "Content-Type: %s/%s", TYPE (a), a->subtype);
 
   if (a->parameter)
   {
     len = 25 + mutt_strlen (a->subtype); /* approximate len. of content-type */
 
     for(p = a->parameter; p; p = p->next)
     {
       char *tmp;
-      
+
       if(!p->value)
 	continue;
-      
+
       fputc (';', f);
 
       buffer[0] = 0;
       tmp = safe_strdup (p->value);
       encode = rfc2231_encode_string (&tmp);
       rfc822_cat (buffer, sizeof (buffer), tmp, MimeSpecials);
 
-      /* Dirty hack to make messages readable by Outlook Express 
+      /* Dirty hack to make messages readable by Outlook Express
        * for the Mac: force quotes around the boundary parameter
        * even when they aren't needed.
        */
 
       if (!ascii_strcasecmp (p->attribute, "boundary") && !strcmp (buffer, tmp))
 	snprintf (buffer, sizeof (buffer), "\"%s\"", tmp);
 
-      safe_free ((void **)&tmp);
+      FREE (&tmp);
 
       tmplen = mutt_strlen (buffer) + mutt_strlen (p->attribute) + 1;
 
       if (len + tmplen + 2 > 76)
       {
 	fputs ("\n\t", f);
