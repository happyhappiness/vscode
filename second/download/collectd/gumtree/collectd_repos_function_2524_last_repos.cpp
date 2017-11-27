int lcc_network_parse(void *data, size_t data_size,
                      lcc_network_parse_options_t opts) {
  if (opts.password_lookup) {
#if HAVE_GCRYPT_H
    int status;
    if ((status = init_gcrypt())) {
      return status;
    }
#else
    return ENOTSUP;
#endif
  }

  return network_parse(data, data_size, NONE, &opts);
}