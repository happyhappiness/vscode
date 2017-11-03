static int var_to_string (int idx, char* val, size_t len)
{
  char tmp[LONG_STRING];
  static const char * const vals[] = { "no", "yes", "ask-no", "ask-yes" };

  tmp[0] = '\0';

  if ((DTYPE(MuttVars[idx].type) == DT_STR) ||
      (DTYPE(MuttVars[idx].type) == DT_PATH) ||
      (DTYPE(MuttVars[idx].type) == DT_RX))
  {
    strfcpy (tmp, NONULL (*((char **) MuttVars[idx].data)), sizeof (tmp));
    if (DTYPE (MuttVars[idx].type) == DT_PATH)
      mutt_pretty_mailbox (tmp, sizeof (tmp));
  }
  else if (DTYPE (MuttVars[idx].type) == DT_ADDR)
  {
    rfc822_write_address (tmp, sizeof (tmp), *((ADDRESS **) MuttVars[idx].data), 0);
  }
  else if (DTYPE (MuttVars[idx].type) == DT_QUAD)
    strfcpy (tmp, vals[quadoption (MuttVars[idx].data)], sizeof (tmp));
  else if (DTYPE (MuttVars[idx].type) == DT_NUM)
  {
    short sval = *((short *) MuttVars[idx].data);

    /* avert your eyes, gentle reader */
    if (mutt_strcmp (MuttVars[idx].option, "wrapmargin") == 0)
      sval = sval > 0 ? 0 : -sval;

    snprintf (tmp, sizeof (tmp), "%d", sval);
  }
  else if (DTYPE (MuttVars[idx].type) == DT_SORT)
  {
    const struct mapping_t *map;
    const char *p;

    switch (MuttVars[idx].type & DT_SUBTYPE_MASK)
    {
      case DT_SORT_ALIAS:
        map = SortAliasMethods;
        break;
      case DT_SORT_BROWSER:
        map = SortBrowserMethods;
        break;
      case DT_SORT_KEYS:
        if ((WithCrypto & APPLICATION_PGP))
          map = SortKeyMethods;
        else
          map = SortMethods;
        break;
      default:
        map = SortMethods;
        break;
    }
    p = mutt_getnamebyvalue (*((short *) MuttVars[idx].data) & SORT_MASK, map);
    snprintf (tmp, sizeof (tmp), "%s%s%s",
              (*((short *) MuttVars[idx].data) & SORT_REVERSE) ? "reverse-" : "",
              (*((short *) MuttVars[idx].data) & SORT_LAST) ? "last-" : "",
              p);
  }
  else if (DTYPE (MuttVars[idx].type) == DT_MAGIC)
  {
    char *p;

    switch (DefaultMagic)
    {
      case MUTT_MBOX:
        p = "mbox";
        break;
      case MUTT_MMDF:
        p = "MMDF";
        break;
      case MUTT_MH:
        p = "MH";
        break;
      case MUTT_MAILDIR:
        p = "Maildir";
        break;
      default:
        p = "unknown";
    }
    strfcpy (tmp, p, sizeof (tmp));
  }
  else if (DTYPE (MuttVars[idx].type) == DT_BOOL)
    strfcpy (tmp, option (MuttVars[idx].data) ? "yes" : "no", sizeof (tmp));
  else
    return 0;

  escape_string (val, len - 1, tmp);

  return 1;
}