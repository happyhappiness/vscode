{
    inuser = Curl_convert_UTF8_to_tchar((char *) user);
    inpass = Curl_convert_UTF8_to_tchar((char *) passwd);

    rc = ldap_bind_s(server, inuser, inpass, method);

    Curl_unicodefree(inuser);
    Curl_unicodefree(inpass);
  }