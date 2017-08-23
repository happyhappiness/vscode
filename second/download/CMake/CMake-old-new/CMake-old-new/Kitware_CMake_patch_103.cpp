@@ -88,7 +88,8 @@
 #  define mp_uintmax_t unsigned long
 #endif
 
-#define BUFFSIZE 256 /* buffer for long-to-str and float-to-str calcs */
+#define BUFFSIZE 326 /* buffer for long-to-str and float-to-str calcs, should
+                        fit negative DBL_MAX (317 letters) */
 #define MAX_PARAMETERS 128 /* lame static limit */
 
 #ifdef __AMIGA__
@@ -299,7 +300,6 @@ static int dprintf_Pass1(const char *format, va_stack_t *vto, char **endpos,
           flags |= FLAGS_ALT;
           break;
         case '.':
-          flags |= FLAGS_PREC;
           if('*' == *fmt) {
             /* The precision is picked from a specified parameter */
 
@@ -498,7 +498,7 @@ static int dprintf_Pass1(const char *format, va_stack_t *vto, char **endpos,
         (mp_intmax_t)va_arg(arglist, int);
     }
 
-    switch (vto[i].type) {
+    switch(vto[i].type) {
     case FORMAT_STRING:
       vto[i].data.str = va_arg(arglist, char *);
       break;
@@ -688,7 +688,7 @@ static int dprintf_formatf(
 
     is_alt = (p->flags & FLAGS_ALT) ? 1 : 0;
 
-    switch (p->type) {
+    switch(p->type) {
     case FORMAT_INT:
       num = p->data.num.as_unsigned;
       if(p->flags & FLAGS_CHAR) {
@@ -913,12 +913,25 @@ static int dprintf_formatf(
         *fptr = 0;
 
         if(width >= 0) {
+          if(width >= (long)sizeof(work))
+            width = sizeof(work)-1;
           /* RECURSIVE USAGE */
           len = curl_msnprintf(fptr, left, "%ld", width);
           fptr += len;
           left -= len;
         }
         if(prec >= 0) {
+          /* for each digit in the integer part, we can have one less
+             precision */
+          size_t maxprec = sizeof(work) - 2;
+          double val = p->data.dnum;
+          while(val >= 10.0) {
+            val /= 10;
+            maxprec--;
+          }
+
+          if(prec > (long)maxprec)
+            prec = (long)maxprec-1;
           /* RECURSIVE USAGE */
           len = curl_msnprintf(fptr, left, ".%ld", prec);
           fptr += len;
@@ -938,7 +951,9 @@ static int dprintf_formatf(
         /* NOTE NOTE NOTE!! Not all sprintf implementations return number of
            output characters */
         (sprintf)(work, formatbuf, p->data.dnum);
-
+#ifdef CURLDEBUG
+        assert(strlen(work) <= sizeof(work));
+#endif
         for(fptr=work; *fptr; fptr++)
           OUTCHAR(*fptr);
       }