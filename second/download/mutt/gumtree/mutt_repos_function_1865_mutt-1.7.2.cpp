static void handle_confline (char *s, FILE *out)
{
  char varname[BUFFSIZE];
  char buff[BUFFSIZE];
  char tmp[BUFFSIZE];
  int type;
  
  char val[BUFFSIZE];

  /* xxx - put this into an actual state machine? */

  /* variable name */
  if (!(s = get_token (varname, sizeof (varname), s))) return;
  
  /* comma */
  if (!(s = get_token (buff, sizeof (buff), s))) return;
    
  /* type */
  if (!(s = get_token (buff, sizeof (buff), s))) return;

  type = buff2type (buff);

  /* possibly a "|" or comma */
  if (!(s = get_token (buff, sizeof (buff), s))) return;

  if (!strcmp (buff, "|"))
  {
    if (Debug) fprintf (stderr, "%s: Expecting <subtype> <comma>.\n", Progname);
    /* ignore subtype and comma */
    if (!(s = get_token (buff, sizeof (buff), s))) return;
    if (!(s = get_token (buff, sizeof (buff), s))) return;
  }

  /* redraw, comma */
  
  while (1)
  {
    if (!(s = get_token (buff, sizeof (buff), s))) return;
    if (!strcmp (buff, ","))
      break;
  }

  /* option name or UL &address */
  if (!(s = get_token (buff, sizeof (buff), s))) return;
  if (!strcmp (buff, "UL"))
    if (!(s = get_token (buff, sizeof (buff), s))) return;

  /* comma */
  if (!(s = get_token (buff, sizeof (buff), s))) return;

  if (Debug) fprintf (stderr, "%s: Expecting default value.\n", Progname);
  
  /* <default value> or UL <default value> */
  if (!(s = get_token (buff, sizeof (buff), s))) return;
  if (!strcmp (buff, "UL"))
  {
    if (Debug) fprintf (stderr, "%s: Skipping UL.\n", Progname);
    if (!(s = get_token (buff, sizeof (buff), s))) return;
  }

  memset (tmp, 0, sizeof (tmp));

  do 
  {
    if (!strcmp (buff, "}"))
      break;

    strncpy (tmp + strlen (tmp), buff, sizeof (tmp) - strlen (tmp));
  }
  while ((s = get_token (buff, sizeof (buff), s)));

  pretty_default (val, sizeof (val), tmp, type);
  print_confline (varname, type, val, out);
}