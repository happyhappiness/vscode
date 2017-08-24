{
    char *dn = p;
    char *unescaped;
    CURLcode result;

    LDAP_TRACE(("DN '%s'\n", dn));

    /* Unescape the DN */
    result = Curl_urldecode(conn->data, dn, 0, &unescaped, NULL, FALSE);
    if(result) {
      rc = LDAP_NO_MEMORY;

      goto quit;
    }

#if defined(USE_WIN32_LDAP)
    /* Convert the unescaped string to a tchar */
    ludp->lud_dn = Curl_convert_UTF8_to_tchar(unescaped);

    /* Free the unescaped string as we are done with it */
    Curl_unicodefree(unescaped);

    if(!ludp->lud_dn) {
      rc = LDAP_NO_MEMORY;

      goto quit;
    }
#else
    ludp->lud_dn = unescaped;
#endif
  }