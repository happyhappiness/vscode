    else
      state_attach_puts (_("[-- Warning: Can't find any signatures. --]\n\n"), s);
  }
  
  rc = mutt_body_handler (a, s);
  
  if (s->flags & MUTT_DISPLAY && sigcnt)
    state_attach_puts (_("\n[-- End of signed data --]\n"), s);
  
  return rc;
}


