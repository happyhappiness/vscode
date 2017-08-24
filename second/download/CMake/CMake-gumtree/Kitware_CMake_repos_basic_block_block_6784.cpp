f(!SSL_CONN_CONFIG(verifypeer)) {
    infof(conn->data, "skipping SSL peer certificate verification\n");
    return SECSuccess;
  }