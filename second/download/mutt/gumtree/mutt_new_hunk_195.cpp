      
      if (maybe_signed)
        a->is_signed_data = 1;
      if(r_is_signed)
        *r_is_signed = -1; /* A signature exists. */

      if ((s->flags & MUTT_DISPLAY))
        state_attach_puts (_("[-- Begin signature "
                             "information --]\n"), s);
      for(idx = 0; (res = show_one_sig_status (ctx, idx, s)) != -1; idx++)
        {
          if (res == 1)
            anybad = 1;
          else if (res == 2)
            anywarn = 1;
        }
      if (!anybad && idx && r_is_signed && *r_is_signed)
        *r_is_signed = anywarn? 2:1; /* Good signature. */
      
      if ((s->flags & MUTT_DISPLAY))
        state_attach_puts (_("[-- End signature "
                             "information --]\n\n"), s);
    }
  gpgme_release (ctx); ctx = NULL;

  fflush (fpout);
