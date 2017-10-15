         state_puts (s->prefix, s);
         state_puts (buffer, s);
       }
       /* check for data on stderr */
       if (fgets (buffer, sizeof(buffer), fperr)) 
       {
-	if (s->flags & M_DISPLAY)
+	if (s->flags & MUTT_DISPLAY)
 	{
 	  state_mark_attach (s);
 	  state_printf (s, _("[-- Autoview stderr of %s --]\n"), command);
 	}
 
 	state_puts (s->prefix, s);
