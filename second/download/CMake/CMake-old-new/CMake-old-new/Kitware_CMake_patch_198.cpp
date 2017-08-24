@@ -5,11 +5,11 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1999 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1999 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
- * are also available at http://curl.haxx.se/docs/copyright.html.
+ * are also available at https://curl.haxx.se/docs/copyright.html.
  *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
@@ -32,15 +32,10 @@
  *
  * If you ever want truly portable and good *printf() clones, the project that
  * took on from here is named 'Trio' and you find more details on the trio web
- * page at http://daniel.haxx.se/trio/
+ * page at https://daniel.haxx.se/projects/trio/
  */
 
 #include "curl_setup.h"
-
-#if defined(DJGPP) && (DJGPP_MINOR < 4)
-#undef _MPRINTF_REPLACE /* don't use x_was_used() here */
-#endif
-
 #include <curl/mprintf.h>
 
 #include "curl_memory.h"
@@ -465,34 +460,40 @@ static long dprintf_Pass1(const char *format, va_stack_t *vto, char **endpos,
       if(flags & FLAGS_WIDTHPARAM) {
         /* we have the width specified from a parameter, so we make that
            parameter's info setup properly */
-        vto[i].width = width - 1;
-        i = width - 1;
-        vto[i].type = FORMAT_WIDTH;
-        vto[i].flags = FLAGS_NEW;
-        vto[i].precision = vto[i].width = 0; /* can't use width or precision
-                                                of width! */
+        long k = width - 1;
+        vto[i].width = k;
+        vto[k].type = FORMAT_WIDTH;
+        vto[k].flags = FLAGS_NEW;
+        /* can't use width or precision of width! */
+        vto[k].width = 0;
+        vto[k].precision = 0;
       }
       if(flags & FLAGS_PRECPARAM) {
         /* we have the precision specified from a parameter, so we make that
            parameter's info setup properly */
-        vto[i].precision = precision - 1;
-        i = precision - 1;
-        vto[i].type = FORMAT_WIDTH;
-        vto[i].flags = FLAGS_NEW;
-        vto[i].precision = vto[i].width = 0; /* can't use width or precision
-                                                of width! */
+        long k = precision - 1;
+        vto[i].precision = k;
+        vto[k].type = FORMAT_WIDTH;
+        vto[k].flags = FLAGS_NEW;
+        /* can't use width or precision of width! */
+        vto[k].width = 0;
+        vto[k].precision = 0;
       }
       *endpos++ = fmt + 1; /* end of this sequence */
     }
   }
 
   /* Read the arg list parameters into our data list */
   for(i=0; i<max_param; i++) {
-    if((i + 1 < max_param) && (vto[i + 1].type == FORMAT_WIDTH)) {
-      /* Width/precision arguments must be read before the main argument
-       * they are attached to
-       */
-      vto[i + 1].data.num.as_signed = (mp_intmax_t)va_arg(arglist, int);
+    /* Width/precision arguments must be read before the main argument
+       they are attached to */
+    if(vto[i].flags & FLAGS_WIDTHPARAM) {
+      vto[vto[i].width].data.num.as_signed =
+        (mp_intmax_t)va_arg(arglist, int);
+    }
+    if(vto[i].flags & FLAGS_PRECPARAM) {
+      vto[vto[i].precision].data.num.as_signed =
+        (mp_intmax_t)va_arg(arglist, int);
     }
 
     switch (vto[i].type) {
@@ -580,6 +581,11 @@ static int dprintf_formatf(
 
   va_stack_t *p;
 
+  /* 'workend' points to the final buffer byte position, but with an extra
+     byte as margin to avoid the (false?) warning Coverity gives us
+     otherwise */
+  char *workend = &work[sizeof(work) - 2];
+
   /* Do the actual %-code parsing */
   dprintf_Pass1(format, vto, endpos, ap_save);
 
@@ -609,6 +615,8 @@ static int dprintf_formatf(
     /* Used to convert negative in positive.  */
     mp_intmax_t signed_num;
 
+    char *w;
+
     if(*f != '%') {
       /* This isn't a format spec, so write everything out until the next one
          OR end of string is reached.  */
@@ -645,16 +653,30 @@ static int dprintf_formatf(
     p = &vto[param];
 
     /* pick up the specified width */
-    if(p->flags & FLAGS_WIDTHPARAM)
+    if(p->flags & FLAGS_WIDTHPARAM) {
       width = (long)vto[p->width].data.num.as_signed;
+      param_num++; /* since the width is extracted from a parameter, we
+                      must skip that to get to the next one properly */
+      if(width < 0) {
+        /* "A negative field width is taken as a '-' flag followed by a
+           positive field width." */
+        width = -width;
+        p->flags |= FLAGS_LEFT;
+        p->flags &= ~FLAGS_PAD_NIL;
+      }
+    }
     else
       width = p->width;
 
     /* pick up the specified precision */
     if(p->flags & FLAGS_PRECPARAM) {
       prec = (long)vto[p->precision].data.num.as_signed;
-      param_num++; /* since the precision is extraced from a parameter, we
+      param_num++; /* since the precision is extracted from a parameter, we
                       must skip that to get to the next one properly */
+      if(prec < 0)
+        /* "A negative precision is taken as if the precision were
+           omitted." */
+        prec = -1;
     }
     else if(p->flags & FLAGS_PREC)
       prec = p->precision;
@@ -715,72 +737,68 @@ static int dprintf_formatf(
 
       number:
       /* Number of base BASE.  */
-      {
-        char *workend = &work[sizeof(work) - 1];
-        char *w;
-
-        /* Supply a default precision if none was given.  */
-        if(prec == -1)
-          prec = 1;
-
-        /* Put the number in WORK.  */
-        w = workend;
-        while(num > 0) {
-          *w-- = digits[num % base];
-          num /= base;
-        }
-        width -= (long)(workend - w);
-        prec -= (long)(workend - w);
 
-        if(is_alt && base == 8 && prec <= 0) {
-          *w-- = '0';
-          --width;
-        }
+      /* Supply a default precision if none was given.  */
+      if(prec == -1)
+        prec = 1;
 
-        if(prec > 0) {
-          width -= prec;
-          while(prec-- > 0)
-            *w-- = '0';
-        }
+      /* Put the number in WORK.  */
+      w = workend;
+      while(num > 0) {
+        *w-- = digits[num % base];
+        num /= base;
+      }
+      width -= (long)(workend - w);
+      prec -= (long)(workend - w);
 
-        if(is_alt && base == 16)
-          width -= 2;
+      if(is_alt && base == 8 && prec <= 0) {
+        *w-- = '0';
+        --width;
+      }
 
-        if(is_neg || (p->flags & FLAGS_SHOWSIGN) || (p->flags & FLAGS_SPACE))
-          --width;
+      if(prec > 0) {
+        width -= prec;
+        while(prec-- > 0)
+          *w-- = '0';
+      }
 
-        if(!(p->flags & FLAGS_LEFT) && !(p->flags & FLAGS_PAD_NIL))
-          while(width-- > 0)
-            OUTCHAR(' ');
+      if(is_alt && base == 16)
+        width -= 2;
 
-        if(is_neg)
-          OUTCHAR('-');
-        else if(p->flags & FLAGS_SHOWSIGN)
-          OUTCHAR('+');
-        else if(p->flags & FLAGS_SPACE)
-          OUTCHAR(' ');
+      if(is_neg || (p->flags & FLAGS_SHOWSIGN) || (p->flags & FLAGS_SPACE))
+        --width;
 
-        if(is_alt && base == 16) {
-          OUTCHAR('0');
-          if(p->flags & FLAGS_UPPER)
-            OUTCHAR('X');
-          else
-            OUTCHAR('x');
-        }
+      if(!(p->flags & FLAGS_LEFT) && !(p->flags & FLAGS_PAD_NIL))
+        while(width-- > 0)
+          OUTCHAR(' ');
 
-        if(!(p->flags & FLAGS_LEFT) && (p->flags & FLAGS_PAD_NIL))
-          while(width-- > 0)
-            OUTCHAR('0');
+      if(is_neg)
+        OUTCHAR('-');
+      else if(p->flags & FLAGS_SHOWSIGN)
+        OUTCHAR('+');
+      else if(p->flags & FLAGS_SPACE)
+        OUTCHAR(' ');
+
+      if(is_alt && base == 16) {
+        OUTCHAR('0');
+        if(p->flags & FLAGS_UPPER)
+          OUTCHAR('X');
+        else
+          OUTCHAR('x');
+      }
 
-        /* Write the number.  */
-        while(++w <= workend) {
-          OUTCHAR(*w);
-        }
+      if(!(p->flags & FLAGS_LEFT) && (p->flags & FLAGS_PAD_NIL))
+        while(width-- > 0)
+          OUTCHAR('0');
 
-        if(p->flags & FLAGS_LEFT)
-          while(width-- > 0)
-            OUTCHAR(' ');
+      /* Write the number.  */
+      while(++w <= workend) {
+        OUTCHAR(*w);
       }
+
+      if(p->flags & FLAGS_LEFT)
+        while(width-- > 0)
+          OUTCHAR(' ');
       break;
 
     case FORMAT_STRING:
@@ -809,7 +827,7 @@ static int dprintf_formatf(
         else
           len = strlen(str);
 
-        width -= (long)len;
+        width -= (len > LONG_MAX) ? LONG_MAX : (long)len;
 
         if(p->flags & FLAGS_ALT)
           OUTCHAR('"');