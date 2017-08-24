{
      char *name;
      size_t name_len;
#if defined(USE_WIN32_LDAP)
      TCHAR *dn = ldap_get_dn(server, entryIterator);
      name = Curl_convert_tchar_to_UTF8(dn);
      if(!name) {
        ldap_memfree(dn);

        result = CURLE_OUT_OF_MEMORY;

        goto quit;
      }
#else
      char *dn = name = ldap_get_dn(server, entryIterator);
#endif
      name_len = strlen(name);

      result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"DN: ", 4);
      if(result) {
#if defined(USE_WIN32_LDAP)
        Curl_unicodefree(name);
#endif
        ldap_memfree(dn);

        goto quit;
      }

      result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *) name,
                                 name_len);
      if(result) {
#if defined(USE_WIN32_LDAP)
        Curl_unicodefree(name);
#endif
        ldap_memfree(dn);

        goto quit;
      }

      result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 1);
      if(result) {
#if defined(USE_WIN32_LDAP)
        Curl_unicodefree(name);
#endif
        ldap_memfree(dn);

        goto quit;
      }

      dlsize += name_len + 5;

#if defined(USE_WIN32_LDAP)
      Curl_unicodefree(name);
#endif
      ldap_memfree(dn);
    }