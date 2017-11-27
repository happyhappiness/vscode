  status = lcc_listval (c, &ret_ident, &ret_ident_num);
  if (status != 0) {
    fprintf (stderr, "ERROR: %s\n", lcc_strerror (c));
    BAIL_OUT (status);
  }

  for (size_t i = 0; i < ret_ident_num; ++i) {
    char id[1024];

    status = lcc_identifier_to_string (c, id, sizeof (id), ret_ident + i);
    if (status != 0) {
      fprintf (stderr, "ERROR: listval: Failed to convert returned "
          "identifier to a string: %s\n", lcc_strerror (c));
