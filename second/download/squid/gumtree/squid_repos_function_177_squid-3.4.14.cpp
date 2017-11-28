static int
BindLDAP(edui_ldap_t *l, char *dn, char *pw, unsigned int t)
{
    int s;
    if (l == NULL) return LDAP_ERR_NULL;
    if (!(l->status & LDAP_INIT_S)) return LDAP_ERR_INIT;		/* Not initalized */
    if (!(l->status & LDAP_OPEN_S)) return LDAP_ERR_OPEN;		/* Not open */
    if (l->status & LDAP_BIND_S) return LDAP_ERR_BIND;			/* Already bound */
    if (l->lp == NULL) return LDAP_ERR_POINTER;				/* Error */

    /* Copy details - dn and pw CAN be NULL for anonymous and/or TLS */
    if (dn != NULL) {
        if ((l->basedn[0] != '\0') && (strstr(dn, l->basedn) == NULL)) {
            /* We got a basedn, but it's not part of dn */
            xstrncpy(l->dn, dn, sizeof(l->dn));
            strncat(l->dn, ",", 1);
            strncat(l->dn, l->basedn, strlen(l->basedn));
        } else
            xstrncpy(l->dn, dn, sizeof(l->dn));
    }
    if (pw != NULL)
        xstrncpy(l->passwd, pw, sizeof(l->passwd));

    /* Type */
    switch (t) {
    case LDAP_AUTH_NONE:
        l->type = t;
        break;
    case LDAP_AUTH_SIMPLE:
        l->type = t;
        break;
    case LDAP_AUTH_SASL:
        l->type = t;
        break;
#ifdef LDAP_AUTH_KRBV4
    case LDAP_AUTH_KRBV4:
        l->type = t;
        break;
#endif
#ifdef LDAP_AUTH_KRBV41
    case LDAP_AUTH_KRBV41:
        l->type = t;
        break;
#endif
#ifdef LDAP_AUTH_KRBV42
    case LDAP_AUTH_KRBV42:
        l->type = t;
        break;
#endif
#ifdef LDAP_AUTH_TLS
    case LDAP_AUTH_TLS:						/* Added for chicken switch to TLS-enabled without using SSL */
        l->type = t;
        break;
#endif
    default:
        l->type = LDAP_AUTH_NONE;
        break;							/* Default to anonymous bind */
    }

    /* Bind */
#if defined(LDAP_AUTH_TLS) && defined(NETSCAPE_SSL) && HAVE_LDAP_START_TLS_S
    if (l->type == LDAP_AUTH_TLS)
        s = ldap_start_tls_s(l->lp, NULL, NULL);
    else
#endif
        s = ldap_bind_s(l->lp, l->dn, l->passwd, l->type);
    if (s == LDAP_SUCCESS) {
        l->status |= LDAP_BIND_S;				/* Success */
        l->err = s;						/* Set LDAP error code */
        return LDAP_ERR_SUCCESS;
    } else {
        l->err = s;						/* Set LDAP error code */
        return LDAP_ERR_FAILED;
    }
}