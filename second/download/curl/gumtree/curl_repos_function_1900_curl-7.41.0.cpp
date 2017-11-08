static int _ldap_url_parse2 (const struct connectdata *conn, LDAPURLDesc *ludp)
{
  int rc = LDAP_SUCCESS;
  char *path;
  char *p;
  char *q;
  size_t i;

  if(!conn->data ||
      !conn->data->state.path ||
      conn->data->state.path[0] != '/' ||
      !checkprefix("LDAP", conn->data->change.url))
    return LDAP_INVALID_SYNTAX;

  ludp->lud_scope = LDAP_SCOPE_BASE;
  ludp->lud_port  = conn->remote_port;
  ludp->lud_host  = conn->host.name;

  /* Duplicate the path */
  p = path = strdup(conn->data->state.path + 1);
  if(!path)
    return LDAP_NO_MEMORY;

  /* Parse the DN (Distinguished Name) */
  q = strchr(p, '?');
  if(q)
    *q++ = '\0';

  if(*p) {
    char *dn = p;
    char *unescaped;

    LDAP_TRACE (("DN '%s'\n", dn));

    /* Unescape the DN */
    unescaped = curl_easy_unescape(conn->data, dn, 0, NULL);
    if(!unescaped) {
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

  p = q;
  if(!p)
    goto quit;

  /* Parse the attributes. skip "??" */
  q = strchr(p, '?');
  if(q)
    *q++ = '\0';

  if(*p) {
    char **attributes;
    size_t count = 0;

    /* Split the string into an array of attributes */
    if(!split_str(p, &attributes, &count)) {
      rc = LDAP_NO_MEMORY;

      goto quit;
    }

    /* Allocate our array (+1 for the NULL entry) */
#if defined(USE_WIN32_LDAP)
    ludp->lud_attrs = calloc(count + 1, sizeof(TCHAR *));
#else
    ludp->lud_attrs = calloc(count + 1, sizeof(char *));
#endif
    if(!ludp->lud_attrs) {
      Curl_safefree(attributes);

      rc = LDAP_NO_MEMORY;

      goto quit;
    }

    for(i = 0; i < count; i++) {
      char *unescaped;

      LDAP_TRACE (("attr[%d] '%s'\n", i, attributes[i]));

      /* Unescape the attribute */
      unescaped = curl_easy_unescape(conn->data, attributes[i], 0, NULL);
      if(!unescaped) {
        Curl_safefree(attributes);

        rc = LDAP_NO_MEMORY;

        goto quit;
      }

#if defined(USE_WIN32_LDAP)
      /* Convert the unescaped string to a tchar */
      ludp->lud_attrs[i] = Curl_convert_UTF8_to_tchar(unescaped);

      /* Free the unescaped string as we are done with it */
      Curl_unicodefree(unescaped);

      if(!ludp->lud_attrs[i]) {
        Curl_safefree(attributes);

        rc = LDAP_NO_MEMORY;

        goto quit;
      }
#else
      ludp->lud_attrs[i] = unescaped;
#endif

      ludp->lud_attrs_dups++;
    }

    Curl_safefree(attributes);
  }

  p = q;
  if(!p)
    goto quit;

  /* Parse the scope. skip "??" */
  q = strchr(p, '?');
  if(q)
    *q++ = '\0';

  if(*p) {
    ludp->lud_scope = str2scope(p);
    if(ludp->lud_scope == -1) {
      rc = LDAP_INVALID_SYNTAX;

      goto quit;
    }
    LDAP_TRACE (("scope %d\n", ludp->lud_scope));
  }

  p = q;
  if(!p)
    goto quit;

  /* Parse the filter */
  q = strchr(p, '?');
  if(q)
    *q++ = '\0';

  if(*p) {
    char *filter = p;
    char *unescaped;

    LDAP_TRACE (("filter '%s'\n", filter));

    /* Unescape the filter */
    unescaped = curl_easy_unescape(conn->data, filter, 0, NULL);
    if(!unescaped) {
      rc = LDAP_NO_MEMORY;

      goto quit;
    }

#if defined(USE_WIN32_LDAP)
    /* Convert the unescaped string to a tchar */
    ludp->lud_filter = Curl_convert_UTF8_to_tchar(unescaped);

    /* Free the unescaped string as we are done with it */
    Curl_unicodefree(unescaped);

    if(!ludp->lud_filter) {
      rc = LDAP_NO_MEMORY;

      goto quit;
    }
#else
    ludp->lud_filter = unescaped;
#endif
  }

  p = q;
  if(p && !*p) {
    rc = LDAP_INVALID_SYNTAX;

    goto quit;
  }

quit:
  Curl_safefree(path);

  return rc;
}