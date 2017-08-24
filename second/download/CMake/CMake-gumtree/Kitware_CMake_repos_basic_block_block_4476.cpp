{
      rc = ldap_bind_s(server, NULL, (TCHAR *)&cred, method);
      Curl_sspi_free_identity(&cred);
    }