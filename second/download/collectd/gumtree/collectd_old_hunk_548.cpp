      BAIL_OUT (status);

    assert (plugins_num == 1);
    plugins[0] = NULL;
  }

  for (i = 0; i < plugins_num; ++i) {
    if (identifiers_num == 0) {
      status = lcc_flush (c, plugins[i], NULL, timeout);
      if (status != 0)
        fprintf (stderr, "ERROR: Failed to flush plugin `%s': %s.\n",
            (plugins[i] == NULL) ? "(all)" : plugins[i], lcc_strerror (c));
    }
    else {
      int j;

      for (j = 0; j < identifiers_num; ++j) {
        status = lcc_flush (c, plugins[i], identifiers + j, timeout);
        if (status != 0) {
          char id[1024];

          lcc_identifier_to_string (c, id, sizeof (id), identifiers + j);
          fprintf (stderr, "ERROR: Failed to flush plugin `%s', "
