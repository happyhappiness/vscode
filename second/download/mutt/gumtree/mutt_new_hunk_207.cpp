	strncpy (t, "no", l);
      break;
    }
    case DT_SORT:
    {
      /* heuristic! */
      if (strncmp (s, "SORT_", 5))
        fprintf (stderr,
                 "WARNING: expected prefix of SORT_ for type DT_SORT instead of %s\n", s);
      strncpy (t, s + 5, l);
      for (; *t; t++) *t = tolower ((unsigned char) *t);
      break;
    }
    case DT_MAGIC:
    {
      /* heuristic! */
      if (strncmp (s, "MUTT_", 5))
        fprintf (stderr,
                 "WARNING: expected prefix of MUTT_ for type DT_MAGIC instead of %s\n", s);
      strncpy (t, s + 5, l);
      for (; *t; t++) *t = tolower ((unsigned char) *t);
      break;
    }
    case DT_STR:
    case DT_RX:
    case DT_ADDR:
