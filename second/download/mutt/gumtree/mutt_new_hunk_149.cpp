    state_attach_puts (_("KeyID "), s);
    state_attach_puts (sig->fpr, s);
    state_attach_puts ("\n", s);
  }

  msglen = mutt_strlen (msg) - 8;
  /* TODO: need to account for msg wide characters
   * and "created" translation length */
  for (i = 0; i < msglen; i++)
    state_attach_puts(" ", s);
  state_attach_puts (_("created: "), s);
  print_time (sig->timestamp, s);
  state_attach_puts ("\n", s);  
}
