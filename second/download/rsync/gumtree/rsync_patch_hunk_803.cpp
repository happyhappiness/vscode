         fprintf(stderr,"\\[%d,%d]", start-match, length);
         do { putc(s->window[start++], stderr); } while (--length != 0);
     }
 }
 #else
 #  define check_match(s, start, match, length)
-#endif
+#endif /* DEBUG */
 
 /* ===========================================================================
  * Fill the window when the lookahead becomes insufficient.
  * Updates strstart and lookahead.
  *
  * IN assertion: lookahead < MIN_LOOKAHEAD
