{
    rc = Curl_create_sspi_identity(user, passwd, &cred);
    if(!rc) {
      rc = ldap_bind_s(server, NULL, (TCHAR *)&cred, method);
      Curl_sspi_free_identity(&cred);
    }
  }