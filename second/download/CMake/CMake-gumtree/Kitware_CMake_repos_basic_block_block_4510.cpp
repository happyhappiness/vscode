f(result) {
#if defined(USE_WIN32_LDAP)
        Curl_unicodefree(name);
#endif
        ldap_memfree(dn);

        goto quit;
      }