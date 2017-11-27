int lcc_server_set_security_level(lcc_server_t *srv, /* {{{ */
                                  lcc_security_level_t level,
                                  const char *username, const char *password) {
  return lcc_network_buffer_set_security_level(srv->buffer, level, username,
                                               password);
}