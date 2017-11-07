static void pretty_default (char *t, size_t l, const char *s, int type)
{
  memset (t, 0, l);
  l--;

  switch (type)
  {
    case DT_QUAD:
    {    
      if (!strcasecmp (s, "M_YES")) strncpy (t, "yes", l);
      else if (!strcasecmp (s, "M_NO")) strncpy (t, "no", l);
      else if (!strcasecmp (s, "M_ASKYES")) strncpy (t, "ask-yes", l);
      else if (!strcasecmp (s, "M_ASKNO")) strncpy (t, "ask-no", l);
      break;
    }
    case DT_BOOL:
    {
      if (atoi (s))
	strncpy (t, "yes", l);
      else
	strncpy (t, "no", l);
      break;
    }
    case DT_SORT:
    {
      /* heuristic! */
      strncpy (t, s + 5, l);
      for (; *t; t++) *t = tolower ((unsigned char) *t);
      break;
    }
    case DT_MAGIC:
    {
      /* heuristic! */
      strncpy (t, s + 2, l);
      for (; *t; t++) *t = tolower ((unsigned char) *t);
      break;
    }
    case DT_STR:
    case DT_RX:
    case DT_ADDR:
    case DT_PATH:
    {
      if (!strcmp (s, "0"))
	break;
      /* fallthrough */
    }
    default:
    {
      strncpy (t, s, l);
      break;
    }
  }
}