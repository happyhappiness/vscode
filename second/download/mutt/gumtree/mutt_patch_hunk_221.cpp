 int query_quadoption (int opt, const char *prompt)
 {
   int v = quadoption (opt);
 
   switch (v)
   {
-    case M_YES:
-    case M_NO:
+    case MUTT_YES:
+    case MUTT_NO:
       return (v);
 
     default:
-      v = mutt_yesorno (prompt, (v == M_ASKYES));
-      CLEARLINE (LINES - 1);
+      v = mutt_yesorno (prompt, (v == MUTT_ASKYES));
+      mutt_window_clearline (MuttMessageWindow, 0);
       return (v);
   }
 
   /* not reached */
 }
 
