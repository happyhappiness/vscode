f(ret/100 != 3) {
    switch(ret) {
    case 504:
      infof(data, "Mechanism %s is not supported by the server (server "
            "returned ftp code: 504).\n", mech->name);
      break;
    case 534:
      infof(data, "Mechanism %s was rejected by the server (server returned "
            "ftp code: 534).\n", mech->name);
      break;
    default:
      if(ret/100 == 5) {
        infof(data, "server does not support the security extensions\n");
        return CURLE_USE_SSL_FAILED;
      }
      break;
    }
    return CURLE_LOGIN_DENIED;
  }