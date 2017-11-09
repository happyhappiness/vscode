static int rfc1524_mailcap_parse (BODY *a,
				  char *filename,
				  char *type, 
				  rfc1524_entry *entry,
				  int opt)
{
  FILE *fp;
  char *buf = NULL;
  size_t buflen;
  char *ch;
  char *field;
  int found = FALSE;
  int copiousoutput;
  int composecommand;
  int editcommand;
  int printcommand;
  int btlen;
  int line = 0;

  /* rfc1524 mailcap file is of the format:
   * base/type; command; extradefs
   * type can be * for matching all
   * base with no /type is an implicit wild
   * command contains a %s for the filename to pass, default to pipe on stdin
   * extradefs are of the form:
   *  def1="definition"; def2="define \;";
   * line wraps with a \ at the end of the line
   * # for comments
   */

  /* find length of basetype */
  if ((ch = strchr (type, '/')) == NULL)
    return FALSE;
  btlen = ch - type;

  if ((fp = fopen (filename, "r")) != NULL)
  {
    while (!found && (buf = mutt_read_line (buf, &buflen, fp, &line, MUTT_CONT)) != NULL)
    {
      /* ignore comments */
      if (*buf == '#')
	continue;
      dprint (2, (debugfile, "mailcap entry: %s\n", buf));

      /* check type */
      ch = get_field (buf);
      if (ascii_strcasecmp (buf, type) &&
	  (ascii_strncasecmp (buf, type, btlen) ||
	   (buf[btlen] != 0 &&			/* implicit wild */
	    mutt_strcmp (buf + btlen, "/*"))))	/* wildsubtype */
	continue;

      /* next field is the viewcommand */
      field = ch;
      ch = get_field (ch);
      if (entry)
	entry->command = safe_strdup (field);

      /* parse the optional fields */
      found = TRUE;
      copiousoutput = FALSE;
      composecommand = FALSE;
      editcommand = FALSE;
      printcommand = FALSE;

      while (ch)
      {
	field = ch;
	ch = get_field (ch);
	dprint (2, (debugfile, "field: %s\n", field));

	if (!ascii_strcasecmp (field, "needsterminal"))
	{
	  if (entry)
	    entry->needsterminal = TRUE;
	}
	else if (!ascii_strcasecmp (field, "copiousoutput"))
	{
	  copiousoutput = TRUE;
	  if (entry)
	    entry->copiousoutput = TRUE;
	}
	else if (!ascii_strncasecmp (field, "composetyped", 12))
	{
	  /* this compare most occur before compose to match correctly */
	  if (get_field_text (field + 12, entry ? &entry->composetypecommand : NULL,
			      type, filename, line))
	    composecommand = TRUE;
	}
	else if (!ascii_strncasecmp (field, "compose", 7))
	{
	  if (get_field_text (field + 7, entry ? &entry->composecommand : NULL,
			      type, filename, line))
	    composecommand = TRUE;
	}
	else if (!ascii_strncasecmp (field, "print", 5))
	{
	  if (get_field_text (field + 5, entry ? &entry->printcommand : NULL,
			      type, filename, line))
	    printcommand = TRUE;
	}
	else if (!ascii_strncasecmp (field, "edit", 4))
	{
	  if (get_field_text (field + 4, entry ? &entry->editcommand : NULL,
			      type, filename, line))
	    editcommand = TRUE;
	}
	else if (!ascii_strncasecmp (field, "nametemplate", 12))
	{
	  get_field_text (field + 12, entry ? &entry->nametemplate : NULL,
			  type, filename, line);
	}
	else if (!ascii_strncasecmp (field, "x-convert", 9))
	{
	  get_field_text (field + 9, entry ? &entry->convert : NULL,
			  type, filename, line);
	}
	else if (!ascii_strncasecmp (field, "test", 4))
	{
	  /* 
	   * This routine executes the given test command to determine
	   * if this is the right entry.
	   */
	  char *test_command = NULL;
	  size_t len;

	  if (get_field_text (field + 4, &test_command, type, filename, line)
	      && test_command)
	  {
	    len = mutt_strlen (test_command) + STRING;
	    safe_realloc (&test_command, len);
	    rfc1524_expand_command (a, a->filename, type, test_command, len);
	    if (mutt_system (test_command))
	    {
	      /* a non-zero exit code means test failed */
	      found = FALSE;
	    }
	    FREE (&test_command);
	  }
	}
      } /* while (ch) */

      if (opt == MUTT_AUTOVIEW)
      {
	if (!copiousoutput)
	  found = FALSE;
      }
      else if (opt == MUTT_COMPOSE)
      {
	if (!composecommand)
	  found = FALSE;
      }
      else if (opt == MUTT_EDIT)
      {
	if (!editcommand)
	  found = FALSE;
      }
      else if (opt == MUTT_PRINT)
      {
	if (!printcommand)
	  found = FALSE;
      }
      
      if (!found)
      {
	/* reset */
	if (entry)
	{
	  FREE (&entry->command);
	  FREE (&entry->composecommand);
	  FREE (&entry->composetypecommand);
	  FREE (&entry->editcommand);
	  FREE (&entry->printcommand);
	  FREE (&entry->nametemplate);
	  FREE (&entry->convert);
	  entry->needsterminal = 0;
	  entry->copiousoutput = 0;
	}
      }
    } /* while (!found && (buf = mutt_read_line ())) */
    safe_fclose (&fp);
  } /* if ((fp = fopen ())) */
  FREE (&buf);
  return found;
}