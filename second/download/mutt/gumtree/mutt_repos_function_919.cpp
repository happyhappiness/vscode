static int get_field_text (char *field, char **entry,
			   char *type, char *filename, int line)
{
  field = mutt_skip_whitespace (field);
  if (*field == '=')
  {
    if (entry)
    {
      field++;
      field = mutt_skip_whitespace (field);
      mutt_str_replace (entry, field);
    }
    return 1;
  }
  else 
  {
    mutt_error (_("Improperly formatted entry for type %s in \"%s\" line %d"),
		type, filename, line);
    return 0;
  }
}