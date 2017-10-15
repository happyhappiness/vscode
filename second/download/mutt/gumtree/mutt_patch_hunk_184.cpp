   if (!h && b->type == TYPETEXT && charset_changed)
   {
     int r;
     snprintf (tmp, sizeof (tmp), _("Convert to %s upon sending?"),
 	      mutt_get_parameter ("charset", b->parameter));
     if ((r = mutt_yesorno (tmp, !b->noconv)) != -1)
-      b->noconv = (r == M_NO);
+      b->noconv = (r == MUTT_NO);
   }
 
   /* inform the user */
   
   snprintf (tmp, sizeof (tmp), "%s/%s", TYPE (b), NONULL (b->subtype));
   if (type_changed)
