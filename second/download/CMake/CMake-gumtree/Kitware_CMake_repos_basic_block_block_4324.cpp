{
    digest = &data->state.proxydigest;
    allocuserpwd = &conn->allocptr.proxyuserpwd;
    userp = conn->http_proxy.user;
    passwdp = conn->http_proxy.passwd;
    authp = &data->state.authproxy;
  }