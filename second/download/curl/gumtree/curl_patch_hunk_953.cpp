         (void)unslashquote(line, param);
       }
       else {
         param = line; /* parameter starts here */
         while(*line && !ISSPACE(*line))
           line++;
-        *line = '\0'; /* zero terminate */
 
-        /* to detect mistakes better, see if there's data following */
-        line++;
-        /* pass all spaces */
-        while(*line && ISSPACE(*line))
-          line++;
+        if(*line) {
+          *line = '\0'; /* zero terminate */
 
-        switch(*line) {
-        case '\0':
-        case '\r':
-        case '\n':
-        case '#': /* comment */
-          break;
-        default:
-          warnf(operation, "%s:%d: warning: '%s' uses unquoted white space in"
-                " the line that may cause side-effects!\n",
-                filename, lineno, option);
+          /* to detect mistakes better, see if there's data following */
+          line++;
+          /* pass all spaces */
+          while(*line && ISSPACE(*line))
+            line++;
+
+          switch(*line) {
+          case '\0':
+          case '\r':
+          case '\n':
+          case '#': /* comment */
+            break;
+          default:
+            warnf(operation->global, "%s:%d: warning: '%s' uses unquoted "
+                  "white space in the line that may cause side-effects!\n",
+                  filename, lineno, option);
+          }
         }
       }
 
       if(!*param) {
         /* do this so getparameter can check for required parameters.
            Otherwise it always thinks there's a parameter. */
