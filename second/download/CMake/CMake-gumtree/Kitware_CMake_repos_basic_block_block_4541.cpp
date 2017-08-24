r(i = 0; i < count; i++) {
      char *unescaped;
      CURLcode result;

      LDAP_TRACE(("attr[%d] '%s'\n", i, attributes[i]));

      /* Unescape the attribute */
      result = Curl_urldecode(conn->data, attributes[i], 0, &unescaped, NULL,
                              FALSE);
      if(result) {
        free(attributes);

        rc = LDAP_NO_MEMORY;

        goto quit;
      }

#if defined(USE_WIN32_LDAP)
      /* Convert the unescaped string to a tchar */
      ludp->lud_attrs[i] = Curl_convert_UTF8_to_tchar(unescaped);

      /* Free the unescaped string as we are done with it */
      Curl_unicodefree(unescaped);

      if(!ludp->lud_attrs[i]) {
        free(attributes);

        rc = LDAP_NO_MEMORY;

        goto quit;
      }
#else
      ludp->lud_attrs[i] = unescaped;
#endif

      ludp->lud_attrs_dups++;
    }