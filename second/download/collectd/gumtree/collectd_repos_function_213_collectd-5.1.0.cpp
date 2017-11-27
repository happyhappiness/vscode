static int listval (lcc_connection_t *c, int argc, char **argv)
{
  lcc_identifier_t *ret_ident     = NULL;
  size_t            ret_ident_num = 0;

  int status;
  size_t i;

  assert (strcasecmp (argv[0], "listval") == 0);

  if (argc != 1) {
    fprintf (stderr, "ERROR: listval: Does not accept any arguments.\n");
    return (-1);
  }

#define BAIL_OUT(s) \
  do { \
    if (ret_ident != NULL) \
      free (ret_ident); \
    ret_ident_num = 0; \
    return (s); \
  } while (0)

  status = lcc_listval (c, &ret_ident, &ret_ident_num);
  if (status != 0) {
    fprintf (stderr, "ERROR: %s\n", lcc_strerror (c));
    BAIL_OUT (status);
  }

  for (i = 0; i < ret_ident_num; ++i) {
    char id[1024];

    status = lcc_identifier_to_string (c, id, sizeof (id), ret_ident + i);
    if (status != 0) {
      fprintf (stderr, "ERROR: listval: Failed to convert returned "
          "identifier to a string: %s\n", lcc_strerror (c));
      continue;
    }

    printf ("%s\n", id);
  }
  BAIL_OUT (0);
#undef BAIL_OUT
}