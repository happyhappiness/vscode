 		    if (verify_result->signatures)
 		      sig_stat = 1;
 		  }
 
                   have_any_sigs = 0;
                   maybe_goodsig = 0;
-                  if ((s->flags & M_DISPLAY) && sig_stat)
+                  if ((s->flags & MUTT_DISPLAY) && sig_stat)
                     {
                       int res, idx;
                       int anybad = 0;
 
                       state_attach_puts (_("[-- Begin signature "
                                            "information --]\n"), s);
