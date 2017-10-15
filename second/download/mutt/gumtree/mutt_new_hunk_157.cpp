    }
  putc ('\n', fp);

  if (key->subkeys)
    {
      s = key->subkeys->fpr;
      /* L10N: DOTFILL */
      fputs (_("Fingerprint: "), fp);
      if (is_pgp && strlen (s) == 40)
        {
          for (i=0; *s && s[1] && s[2] && s[3] && s[4]; s += 4, i++)
            {
              putc (*s, fp);
