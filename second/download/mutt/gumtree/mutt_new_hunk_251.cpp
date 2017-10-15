      safe_fclose (&fpout);
      mutt_unlink (tmptmpfname);
    }
    fpout = NULL;
  }

  if (s->flags & MUTT_DISPLAY)
  {
    if (type & ENCRYPT)
      state_attach_puts (_("\n[-- End of S/MIME encrypted data. --]\n"), s);
    else
      state_attach_puts (_("\n[-- End of S/MIME signed data. --]\n"), s);
  }
