static oconfig_item_t *oconfig_parse_fh(FILE *fh) {
  int status;
  oconfig_item_t *ret;

  char file[10];

  yyset_in(fh);

  if (NULL == c_file) {
    status = snprintf(file, sizeof(file), "<fd#%d>", fileno(fh));

    if ((status < 0) || (((size_t)status) >= sizeof(file))) {
      c_file = "<unknown>";
    } else {
      file[sizeof(file) - 1] = '\0';
      c_file = file;
    }
  }

  status = yyparse();
  if (status != 0) {
    fprintf(stderr, "yyparse returned error #%i\n", status);
    return (NULL);
  }

  c_file = NULL;

  ret = ci_root;
  ci_root = NULL;
  yyset_in((FILE *)0);

  return (ret);
}