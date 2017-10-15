               *PgpPass = 0;
 	    fprintf (pgpin, "%s\n", PgpPass);
 	  }
 	  
 	  safe_fclose (&pgpin);
 
-	  if (s->flags & M_DISPLAY)
+	  if (s->flags & MUTT_DISPLAY)
 	  {
 	    crypt_current_time (s, "PGP");
 	    rc = pgp_copy_checksig (pgperr, s->fpout);
 	  }
 	  
 	  safe_fclose (&pgperr);
 	  rv = mutt_wait_filter (thepid);
 	  
-	  if (s->flags & M_DISPLAY)
+	  if (s->flags & MUTT_DISPLAY)
 	  {
 	    if (rc == 0) have_any_sigs = 1;
 	    /*
 	     * Sig is bad if
 	     * gpg_good_sign-pattern did not match || pgp_decode_command returned not 0
 	     * Sig _is_ correct if
