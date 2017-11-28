static int
SearchIPLDAP(edui_ldap_t *l)
{
    ber_len_t i, x;
    ber_len_t j, k;
    ber_len_t y, z;
    int c;
    char bufa[EDUI_MAXLEN], bufb[EDUI_MAXLEN], hexc[4];
    LDAPMessage *ent;
    if (l == NULL) return LDAP_ERR_NULL;
    if (l->lp == NULL) return LDAP_ERR_POINTER;
    if (!(l->status & LDAP_INIT_S)) return LDAP_ERR_INIT;               /* Not initalized */
    if (!(l->status & LDAP_OPEN_S)) return LDAP_ERR_OPEN;               /* Not open */
    if (!(l->status & LDAP_BIND_S)) return LDAP_ERR_BIND;               /* Not bound */
    if (!(l->status & LDAP_SEARCH_S)) return LDAP_ERR_NOT_SEARCHED;         /* Not searched */
    if (l->num_ent <= 0) {
        debug("l->num_ent: %d\n", l->num_ent);
        return LDAP_ERR_DATA;                               /* No entries found */
    }
    if (l->val != NULL)
        ldap_value_free_len(l->val);                            /* Clear data before populating */
    l->num_val = 0;
    if (l->status & LDAP_VAL_S)
        l->status &= ~(LDAP_VAL_S);                         /* Clear VAL bit */
    if (edui_conf.attrib[0] == '\0')
        xstrncpy(edui_conf.attrib, "cn", sizeof(edui_conf.attrib));         /* Make sure edui_conf.attrib is set */

    /* Sift through entries */
    struct berval **ber = NULL;
    for (ent = ldap_first_entry(l->lp, l->lm); ent != NULL; ent = ldap_next_entry(l->lp, ent)) {
        l->val = ldap_get_values_len(l->lp, ent, "networkAddress");
        ber = ldap_get_values_len(l->lp, ent, edui_conf.attrib);            /* edui_conf.attrib is the <userid> mapping */
        if (l->val != NULL) {
            x = ldap_count_values_len(l->val);                      /* We got x values ... */
            l->num_val = x;
            if (x > 0) {
                /* Display all values */
                for (i = 0; i < x; ++i) {
                    j = l->val[i]->bv_len;
                    memcpy(bufa, l->val[i]->bv_val, j);
                    z = BinarySplit(bufa, j, '#', bufb, sizeof(bufb));
                    /* BINARY DEBUGGING *
                                              local_printfx("value[%" PRIuSIZE "]: BinarySplit(", (size_t) i);
                                              for (k = 0; k < z; ++k) {
                                                c = (int) bufb[k];
                                                if (c < 0)
                                                  c = c + 256;
                                                local_printfx("%02X", c);
                                              }
                                              local_printfx(", ");
                                              for (k = 0; k < (j - z - 1); ++k) {
                                                c = (int) bufa[k];
                                                if (c < 0)
                                                  c = c + 256;
                                                local_printfx("%02X", c);
                                              }
                                              local_printfx("): %" PRIuSIZE "\n", (size_t) z);
                    * BINARY DEBUGGING */
                    z = j - z - 1;
                    j = atoi(bufb);
                    if (j == 1) {
                        /* IPv4 address (eDirectory 8.7 and below) */
                        /* bufa is the address, just compare it */
                        if (!(l->status & LDAP_IPV4_S) || (l->status & LDAP_IPV6_S))
                            break;                          /* Not looking for IPv4 */
                        for (k = 0; k < z; ++k) {
                            c = (int) bufa[k];
                            if (c < 0)
                                c = c + 256;
                            int hlen = snprintf(hexc, sizeof(hexc), "%02X", c);
                            if (k == 0)
                                xstrncpy(bufb, hexc, sizeof(bufb));
                            else
                                strncat(bufb, hexc, hlen);
                        }
                        y = strlen(bufb);
                        /* Compare value with IP */
                        if (memcmp(l->search_ip, bufb, y) == 0) {
                            /* We got a match! - Scan 'ber' for 'cn' values */
                            z = ldap_count_values_len(ber);
                            for (j = 0; j < z; ++j) {
// broken?                        xstrncpy(l->userid, ber[j]->bv_val, min(sizeof(l->userid),static_cast<size_t>(ber[j]->bv_len)));
                                xstrncpy(l->userid, ber[j]->bv_val, sizeof(l->userid));
                                /* Using bv_len of min() breaks the result by 2 chars */
                            }
                            ldap_value_free_len(l->val);
                            l->val = NULL;
                            ldap_value_free_len(ber);
                            ber = NULL;
                            l->num_val = 0;
                            l->err = LDAP_SUCCESS;
                            l->status &= ~(LDAP_SEARCH_S);
                            return LDAP_ERR_SUCCESS;                /* We got our userid */
                        }
                        /* Not matched, continue */
                    } else if ((j == 8) || (j == 9)) {
                        /* IPv4 (UDP/TCP) address (eDirectory 8.8 and higher) */
                        /* bufa + 2 is the address (skip 2 digit port) */
                        if (!(l->status & LDAP_IPV4_S) || (l->status & LDAP_IPV6_S))
                            break;                          /* Not looking for IPv4 */
                        for (k = 2; k < z; ++k) {
                            c = (int) bufa[k];
                            if (c < 0)
                                c = c + 256;
                            int hlen = snprintf(hexc, sizeof(hexc), "%02X", c);
                            if (k == 2)
                                xstrncpy(bufb, hexc, sizeof(bufb));
                            else
                                strncat(bufb, hexc, hlen);
                        }
                        y = strlen(bufb);
                        /* Compare value with IP */
                        if (memcmp(l->search_ip, bufb, y) == 0) {
                            /* We got a match! - Scan 'ber' for 'cn' values */
                            z = ldap_count_values_len(ber);
                            for (j = 0; j < z; ++j) {
// broken?                        xstrncpy(l->userid, ber[j]->bv_val, min(sizeof(l->userid),static_cast<size_t>(ber[j]->bv_len)));
                                xstrncpy(l->userid, ber[j]->bv_val, sizeof(l->userid));
                                /* Using bv_len of min() breaks the result by 2 chars */
                            }
                            ldap_value_free_len(l->val);
                            l->val = NULL;
                            ldap_value_free_len(ber);
                            ber = NULL;
                            l->num_val = 0;
                            l->err = LDAP_SUCCESS;
                            l->status &= ~(LDAP_SEARCH_S);
                            return LDAP_ERR_SUCCESS;                /* We got our userid */
                        }
                        /* Not matched, continue */
                    } else if ((j == 10) || (j == 11)) {
                        /* IPv6 (UDP/TCP) address (eDirectory 8.8 and higher) */
                        /* bufa + 2 is the address (skip 2 digit port) */
                        if (!(l->status & LDAP_IPV6_S))
                            break;                          /* Not looking for IPv6 */
                        for (k = 2; k < z; ++k) {
                            c = (int) bufa[k];
                            if (c < 0)
                                c = c + 256;
                            int hlen = snprintf(hexc, sizeof(hexc), "%02X", c);
                            if (k == 2)
                                xstrncpy(bufb, hexc, sizeof(bufb));
                            else
                                strncat(bufb, hexc, hlen);
                        }
                        y = strlen(bufb);
                        /* Compare value with IP */
                        if (memcmp(l->search_ip, bufb, y) == 0) {
                            /* We got a match! - Scan 'ber' for 'cn' values */
                            z = ldap_count_values_len(ber);
                            for (j = 0; j < z; ++j) {
// broken?                        xstrncpy(l->userid, ber[j]->bv_val, min(sizeof(l->userid),static_cast<size_t>(ber[j]->bv_len)));
                                xstrncpy(l->userid, ber[j]->bv_val, sizeof(l->userid));
                                /* Using bv_len of min() breaks the result by 2 chars */
                            }
                            ldap_value_free_len(l->val);
                            l->val = NULL;
                            ldap_value_free_len(ber);
                            ber = NULL;
                            l->num_val = 0;
                            l->err = LDAP_SUCCESS;
                            l->status &= ~(LDAP_SEARCH_S);
                            return LDAP_ERR_SUCCESS;                /* We got our userid */
                        }
                        /* Not matched, continue */
                    }
//          else {
                    /* Others are unsupported */
//                    }
                }
                if (ber != NULL) {
                    ldap_value_free_len(ber);
                    ber = NULL;
                }
            }
            ldap_value_free_len(l->val);
            l->val = NULL;
        }
        if (ber != NULL) {
            ldap_value_free_len(ber);
            ber = NULL;
        }
        /* Attr not found, continue */
    }
    /* No entries found using given attr */
    if (l->val != NULL) {
        ldap_value_free_len(l->val);
        l->val = NULL;
    }
    if (l->lm != NULL) {
        ldap_msgfree(l->lm);
        l->lm = NULL;
    }
    l->num_ent = 0;
    l->num_val = 0;
    l->err = LDAP_NO_SUCH_OBJECT;
    l->status &= ~(LDAP_SEARCH_S);
    return LDAP_ERR_NOTFOUND;                       /* Not found ... Sorry :) */
}