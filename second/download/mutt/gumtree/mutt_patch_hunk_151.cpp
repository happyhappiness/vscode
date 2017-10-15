       else /* can't decide (yellow) */
       {
         print_smime_keyinfo (_("Problem signature from:"), sig, key, s);
 	/* 0 indicates no expiration */
 	if (sig->exp_timestamp)
 	{
+          /* L10N:
+             This is trying to match the width of the
+             "Problem signature from:" translation just above. */
 	  state_attach_puts (_("               expires: "), s);
 	  print_time (sig->exp_timestamp, s);
 	  state_attach_puts ("\n", s);
 	}
 	show_sig_summary (sum, ctx, key, idx, s, sig);
         anywarn = 1;
