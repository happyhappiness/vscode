 
 int mutt_change_flag (HEADER *h, int bf)
 {
   int i, flag;
   event_t event;
 
-  mvprintw (LINES - 1, 0, "%s? (D/N/O/r/*/!): ", bf ? _("Set flag") : _("Clear flag"));
-  clrtoeol ();
+  mutt_window_mvprintw (MuttMessageWindow, 0, 0,
+                        "%s? (D/N/O/r/*/!): ", bf ? _("Set flag") : _("Clear flag"));
+  mutt_window_clrtoeol (MuttMessageWindow);
 
   event = mutt_getch();
   i = event.ch;
   if (i < 0)
   {
-    CLEARLINE (LINES-1);
+    mutt_window_clearline (MuttMessageWindow, 0);
     return (-1);
   }
 
-  CLEARLINE (LINES-1);
+  mutt_window_clearline (MuttMessageWindow, 0);
 
   switch (i)
   {
     case 'd':
     case 'D':
-      flag = M_DELETE;
+      if (!bf)
+      {
+        if (h)
+          mutt_set_flag (Context, h, MUTT_PURGE, bf);
+        else
+          mutt_tag_set_flag (MUTT_PURGE, bf);
+      }
+      flag = MUTT_DELETE;
       break;
 
     case 'N':
     case 'n':
-      flag = M_NEW;
+      flag = MUTT_NEW;
       break;
 
     case 'o':
     case 'O':
       if (h)
-	mutt_set_flag (Context, h, M_READ, !bf);
+	mutt_set_flag (Context, h, MUTT_READ, !bf);
       else
-	mutt_tag_set_flag (M_READ, !bf);
-      flag = M_OLD;
+	mutt_tag_set_flag (MUTT_READ, !bf);
+      flag = MUTT_OLD;
       break;
 
     case 'r':
     case 'R':
-      flag = M_REPLIED;
+      flag = MUTT_REPLIED;
       break;
 
     case '*':
-      flag = M_TAG;
+      flag = MUTT_TAG;
       break;
 
     case '!':
-      flag = M_FLAG;
+      flag = MUTT_FLAG;
       break;
 
     default:
       BEEP ();
       return (-1);
   }
