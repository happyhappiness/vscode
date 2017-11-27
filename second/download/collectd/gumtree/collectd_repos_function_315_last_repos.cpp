static int apcups_read(void) {
  apc_detail_t apcups_detail = {
      .linev = NAN,
      .outputv = NAN,
      .battv = NAN,
      .loadpct = NAN,
      .bcharge = NAN,
      .timeleft = NAN,
      .itemp = NAN,
      .linefreq = NAN,
  };

  int status = apc_query_server(conf_node, conf_service, &apcups_detail);

  if (status != 0) {
    DEBUG("apcups plugin: apc_query_server (\"%s\", \"%s\") = %d",
          conf_node, conf_service, status);
    return status;
  }

  apc_submit(&apcups_detail);

  return 0;
}