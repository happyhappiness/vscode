  int status;

  assert(strcasecmp(argv[0], "listval") == 0);

  if (argc != 1) {
    fprintf(stderr, "ERROR: listval: Does not accept any arguments.\n");
    return -1;
  }

#define BAIL_OUT(s)                                                            \
  do {                                                                         \
    if (ret_ident != NULL)                                                     \
      free(ret_ident);                                                         \
    ret_ident_num = 0;                                                         \
    return s;                                                                  \
  } while (0)

  status = lcc_listval(c, &ret_ident, &ret_ident_num);
  if (status != 0) {
    fprintf(stderr, "ERROR: %s\n", lcc_strerror(c));
    BAIL_OUT(status);
