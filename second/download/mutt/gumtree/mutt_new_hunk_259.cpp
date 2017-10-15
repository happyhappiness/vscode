
  /* just in case print remaining odd digits */
  for (; *s; s++)
    *p++ = *s;
  *p++ = '\n';
  *p = 0;
  state_puts (buf, state);
  FREE (&buf);
}

/* Show the validity of a key used for one signature. */
static void show_one_sig_validity (gpgme_ctx_t ctx, int idx, STATE *s)
{
