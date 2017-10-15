      tm = localtime (&tt);
#ifdef HAVE_LANGINFO_D_T_FMT
      strftime (shortbuf, sizeof shortbuf, nl_langinfo (D_T_FMT), tm);
#else
      strftime (shortbuf, sizeof shortbuf, "%c", tm);
#endif
      fprintf (fp, _("Valid From : %s\n"), shortbuf);
    }
  
  if (key->subkeys && (key->subkeys->expires > 0))
    {
      tt = key->subkeys->expires;
