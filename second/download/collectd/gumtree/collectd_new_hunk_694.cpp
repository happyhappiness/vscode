
  status = lcc_string_to_identifier(connection, &ident, ident_str);
  if (status != 0) {
    printf("ERROR: Creating an identifier failed: %s.\n",
           lcc_strerror(connection));
    LCC_DESTROY(connection);
    return RET_CRITICAL;
  }

  status = lcc_getval(connection, &ident, &values_num, &values, &values_names);
  if (status != 0) {
    printf("ERROR: Retrieving values from the daemon failed: %s.\n",
           lcc_strerror(connection));
    LCC_DESTROY(connection);
    return RET_CRITICAL;
  }

  LCC_DESTROY(connection);

  status = filter_ds(&values_num, &values, &values_names);
  if (status != RET_OKAY)
    return status;

  status = RET_UNKNOWN;
  if (consolitation_g == CON_NONE)
    status = do_check_con_none(values_num, values, values_names);
  else if (consolitation_g == CON_AVERAGE)
    status = do_check_con_average(values_num, values, values_names);
