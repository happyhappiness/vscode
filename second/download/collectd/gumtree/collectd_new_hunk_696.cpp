  address[sizeof(address) - 1] = 0;

  connection = NULL;
  status = lcc_connect(address, &connection);
  if (status != 0) {
    printf("ERROR: Connecting to daemon at %s failed.\n", socket_file_g);
    return RET_CRITICAL;
  }

  if (0 == strcasecmp(value_string_g, "LIST"))
    return do_listval(connection);

  return do_check(connection);
} /* int main */
