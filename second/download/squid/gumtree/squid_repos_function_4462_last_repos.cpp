size_t
get_attributes(LDAP * ld, LDAPMessage * res, const char *attribute,
               char ***ret_value)
{

    char **attr_value = *ret_value;
    size_t max_attr = 0;

    /*
     * loop over attributes
     */
    debug((char *) "%s| %s: DEBUG: Search ldap entries for attribute : %s\n",
          LogTime(), PROGRAM, attribute);
    for (LDAPMessage * msg = ldap_first_entry(ld, res); msg;
            msg = ldap_next_entry(ld, msg)) {

        switch (ldap_msgtype(msg)) {

        case LDAP_RES_SEARCH_ENTRY: {
            BerElement *b = NULL;
            for (char *attr = ldap_first_attribute(ld, msg, &b); attr;
                    attr = ldap_next_attribute(ld, msg, b)) {
                if (strcasecmp(attr, attribute) == 0) {
                    struct berval **values;

                    if ((values =
                                ldap_get_values_len(ld, msg, attr)) != NULL) {
                        for (int il = 0; values[il] != NULL; ++il) {

                            attr_value =
                                (char **) xrealloc(attr_value,
                                                   (max_attr + 1) * sizeof(char *));
                            if (!attr_value)
                                break;

                            attr_value[max_attr] =
                                (char *) xmalloc(values[il]->bv_len + 1);
                            memcpy(attr_value[max_attr], values[il]->bv_val,
                                   values[il]->bv_len);
                            attr_value[max_attr][values[il]->bv_len] = 0;
                            max_attr++;
                        }
                    }
                    ber_bvecfree(values);
                }
                ldap_memfree(attr);
            }
            ber_free(b, 0);
        }
        break;
        case LDAP_RES_SEARCH_REFERENCE:
            debug((char *)
                  "%s| %s: DEBUG: Received a search reference message\n",
                  LogTime(), PROGRAM);
            break;
        case LDAP_RES_SEARCH_RESULT:
            debug((char *) "%s| %s: DEBUG: Received a search result message\n",
                  LogTime(), PROGRAM);
            break;
        default:
            break;
        }
    }

    debug((char *) "%s| %s: DEBUG: %" PRIuSIZE
          " ldap entr%s found with attribute : %s\n", LogTime(), PROGRAM,
          max_attr, max_attr > 1 || max_attr == 0 ? "ies" : "y", attribute);

    *ret_value = attr_value;
    return max_attr;
}