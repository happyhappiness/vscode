int mutt_command_complete (char *buffer, size_t len, int pos, int numtabs)
{
  char *pt = buffer;
  int num;
  int spaces; /* keep track of the number of leading spaces on the line */
  myvar_t *myv;

  SKIPWS (buffer);
  spaces = buffer - pt;

  pt = buffer + pos - spaces;
  while ((pt > buffer) && !isspace ((unsigned char) *pt))
    pt--;

  if (pt == buffer) /* complete cmd */
  {
    /* first TAB. Collect all the matches */
    if (numtabs == 1)
    {
      Num_matched = 0;
      strfcpy (User_typed, pt, sizeof (User_typed));
      memset (Matches, 0, Matches_listsize);
      memset (Completed, 0, sizeof (Completed));
      for (num = 0; Commands[num].name; num++)
	candidate (Completed, User_typed, Commands[num].name, sizeof (Completed));
      matches_ensure_morespace (Num_matched);
      Matches[Num_matched++] = User_typed;

      /* All matches are stored. Longest non-ambiguous string is ""
       * i.e. don't change 'buffer'. Fake successful return this time */
      if (User_typed[0] == 0)
	return 1;
    }

    if (Completed[0] == 0 && User_typed[0])
      return 0;

     /* Num_matched will _always_ be at least 1 since the initial
      * user-typed string is always stored */
    if (numtabs == 1 && Num_matched == 2)
      snprintf(Completed, sizeof(Completed),"%s", Matches[0]);
    else if (numtabs > 1 && Num_matched > 2)
      /* cycle thru all the matches */
      snprintf(Completed, sizeof(Completed), "%s", 
	       Matches[(numtabs - 2) % Num_matched]);

    /* return the completed command */
    strncpy (buffer, Completed, len - spaces);
  }
  else if (!mutt_strncmp (buffer, "set", 3)
	   || !mutt_strncmp (buffer, "unset", 5)
	   || !mutt_strncmp (buffer, "reset", 5)
	   || !mutt_strncmp (buffer, "toggle", 6))
  { 		/* complete variables */
    static const char * const prefixes[] = { "no", "inv", "?", "&", 0 };
    
    pt++;
    /* loop through all the possible prefixes (no, inv, ...) */
    if (!mutt_strncmp (buffer, "set", 3))
    {
      for (num = 0; prefixes[num]; num++)
      {
	if (!mutt_strncmp (pt, prefixes[num], mutt_strlen (prefixes[num])))
	{
	  pt += mutt_strlen (prefixes[num]);
	  break;
	}
      }
    }
    
    /* first TAB. Collect all the matches */
    if (numtabs == 1)
    {
      Num_matched = 0;
      strfcpy (User_typed, pt, sizeof (User_typed));
      memset (Matches, 0, Matches_listsize);
      memset (Completed, 0, sizeof (Completed));
      for (num = 0; MuttVars[num].option; num++)
	candidate (Completed, User_typed, MuttVars[num].option, sizeof (Completed));
      for (myv = MyVars; myv; myv = myv->next)
	candidate (Completed, User_typed, myv->name, sizeof (Completed));
      matches_ensure_morespace (Num_matched);
      Matches[Num_matched++] = User_typed;

      /* All matches are stored. Longest non-ambiguous string is ""
       * i.e. don't change 'buffer'. Fake successful return this time */
      if (User_typed[0] == 0)
	return 1;
    }

    if (Completed[0] == 0 && User_typed[0])
      return 0;

    /* Num_matched will _always_ be at least 1 since the initial
     * user-typed string is always stored */
    if (numtabs == 1 && Num_matched == 2)
      snprintf(Completed, sizeof(Completed),"%s", Matches[0]);
    else if (numtabs > 1 && Num_matched > 2)
    /* cycle thru all the matches */
      snprintf(Completed, sizeof(Completed), "%s", 
	       Matches[(numtabs - 2) % Num_matched]);

    strncpy (pt, Completed, buffer + len - pt - spaces);
  }
  else if (!mutt_strncmp (buffer, "exec", 4))
  {
    const struct binding_t *menu = km_get_table (CurrentMenu);

    if (!menu && CurrentMenu != MENU_PAGER)
      menu = OpGeneric;
    
    pt++;
    /* first TAB. Collect all the matches */
    if (numtabs == 1)
    {
      Num_matched = 0;
      strfcpy (User_typed, pt, sizeof (User_typed));
      memset (Matches, 0, Matches_listsize);
      memset (Completed, 0, sizeof (Completed));
      for (num = 0; menu[num].name; num++)
	candidate (Completed, User_typed, menu[num].name, sizeof (Completed));
      /* try the generic menu */
      if (Completed[0] == 0 && CurrentMenu != MENU_PAGER) 
      {
	menu = OpGeneric;
	for (num = 0; menu[num].name; num++)
	  candidate (Completed, User_typed, menu[num].name, sizeof (Completed));
      }
      matches_ensure_morespace (Num_matched);
      Matches[Num_matched++] = User_typed;

      /* All matches are stored. Longest non-ambiguous string is ""
       * i.e. don't change 'buffer'. Fake successful return this time */
      if (User_typed[0] == 0)
	return 1;
    }

    if (Completed[0] == 0 && User_typed[0])
      return 0;

    /* Num_matched will _always_ be at least 1 since the initial
     * user-typed string is always stored */
    if (numtabs == 1 && Num_matched == 2)
      snprintf(Completed, sizeof(Completed),"%s", Matches[0]);
    else if (numtabs > 1 && Num_matched > 2)
    /* cycle thru all the matches */
      snprintf(Completed, sizeof(Completed), "%s", 
	       Matches[(numtabs - 2) % Num_matched]);

    strncpy (pt, Completed, buffer + len - pt - spaces);
  }
  else
    return 0;

  return 1;
}