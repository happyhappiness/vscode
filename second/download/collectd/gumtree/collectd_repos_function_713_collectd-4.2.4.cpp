oconfig_item_t *oconfig_parse_fh (FILE *fh)
{
  int status;
  oconfig_item_t *ret;

  yyset_in (fh);

  status = yyparse ();
  if (status != 0)
  {
    fprintf (stderr, "yyparse returned error #%i\n", status);
    return (NULL);
  }

  ret = ci_root;
  ci_root = NULL;
  yyset_in ((FILE *) 0);

  return (ret);
}