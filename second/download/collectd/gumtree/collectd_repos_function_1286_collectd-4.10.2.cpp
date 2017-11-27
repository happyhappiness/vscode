static int olsrd_read_table (FILE *fh, /* {{{ */
    int (*callback) (int lineno, size_t fields_num, char **fields))
{
  char buffer[1024];
  size_t buffer_len;

  char *fields[32];
  size_t fields_num;

  int lineno;

  lineno = 0;
  while (fgets (buffer, sizeof (buffer), fh) != NULL)
  {
    /* An empty line ends the table. */
    buffer_len = strchomp (buffer);
    if (buffer_len <= 0)
    {
      (*callback) (lineno, /* fields_num = */ 0, /* fields = */ NULL);
      break;
    }

    fields_num = strtabsplit (buffer, fields, STATIC_ARRAY_SIZE (fields));

    (*callback) (lineno, fields_num, fields);
    lineno++;
  } /* while (fgets) */
  
  return (0);
}