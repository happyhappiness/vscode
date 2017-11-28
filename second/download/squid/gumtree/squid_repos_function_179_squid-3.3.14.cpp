static int
ConvertIP(edui_ldap_t *l, char *ip)
{
    char bufa[EDUI_MAXLEN], bufb[EDUI_MAXLEN], obj[EDUI_MAXLEN];
    char hexc[4], *p;
    void *y, *z;
    size_t s;
    long x;
    int i, j, t, swi;							/* IPv6 "::" cut over toggle */
    if (l == NULL) return LDAP_ERR_NULL;
    if (ip == NULL) return LDAP_ERR_PARAM;
    if (!(l->status & LDAP_INIT_S)) return LDAP_ERR_INIT;		/* Not initalized */
    if (!(l->status & LDAP_OPEN_S)) return LDAP_ERR_OPEN;		/* Not open */
    if (!(l->status & LDAP_BIND_S)) return LDAP_ERR_BIND;		/* Not bound */

    y = memchr((void *)ip, ':', EDUI_MAXLEN);
    z = memchr((void *)ip, '.', EDUI_MAXLEN);
    if ((y != NULL) && (z != NULL)) {
        y = NULL;
        z = NULL;
        return LDAP_ERR_INVALID;
    }
    if ((y != NULL) && (edui_conf.mode & EDUI_MODE_IPV4)) {
        /* IPv4 Mode forced */
        return LDAP_ERR_INVALID;
    } else if (y != NULL) {
        /* Set IPv6 mode */
        if (l->status & LDAP_IPV4_S)
            l->status &= ~(LDAP_IPV4_S);
        if (!(l->status & LDAP_IPV6_S))
            l->status |= (LDAP_IPV6_S);
        y = NULL;
    }
    if ((z != NULL) && (edui_conf.mode & EDUI_MODE_IPV6)) {
        /* IPv6 Mode forced */
        return LDAP_ERR_INVALID;
    } else if (z != NULL) {
        /* Set IPv4 mode */
        if (l->status & LDAP_IPV6_S)
            l->status &= ~(LDAP_IPV6_S);
        if (!(l->status & LDAP_IPV4_S))
            l->status |= (LDAP_IPV4_S);
        z = NULL;
    }
    s = strlen(ip);
    *(bufa) = '\0';
    *(bufb) = '\0';
    *(obj) = '\0';
    /* StringSplit() will zero out bufa & obj at each call */
    memset(l->search_ip, '\0', sizeof(l->search_ip));
    xstrncpy(bufa, ip, sizeof(bufa));						/* To avoid segfaults, use bufa instead of ip */
    swi = 0;
    if (l->status & LDAP_IPV6_S) {
        /* Search for :: in string */
        if ((bufa[0] == ':') && (bufa[1] == ':')) {
            /* bufa starts with a ::, so just copy and clear */
            xstrncpy(bufb, bufa, sizeof(bufb));
            *(bufa) = '\0';
            ++swi;								/* Indicates that there is a bufb */
        } else if ((bufa[0] == ':') && (bufa[1] != ':')) {
            /* bufa starts with a :, a typo so just fill in a ':', cat and clear */
            bufb[0] = ':';
            strncat(bufb, bufa, strlen(bufa));
            *(bufa) = '\0';
            ++swi;								/* Indicates that there is a bufb */
        } else {
            p = strstr(bufa, "::");
            if (p != NULL) {
                /* Found it, break bufa down and split into bufb here */
                *(bufb) = '\0';
                i = strlen(p);
                memcpy(bufb, p, i);
                *p = '\0';
                bufb[i] = '\0';
                ++swi;								/* Indicates that there is a bufb */
            }
        }
    }
    s = strlen(bufa);
    if (s < 1)
        s = strlen(bufb);
    while (s > 0) {
        if ((l->status & LDAP_IPV4_S) && (swi == 0)) {
            /* Break down IPv4 address  */
            t = StringSplit(bufa, '.', obj, sizeof(obj));
            if (t > 0) {
                errno = 0;
                x = strtol(obj, (char **)NULL, 10);
                if (((x < 0) || (x > 255)) || ((errno != 0) && (x == 0)) || ((obj[0] != '0') && (x == 0)))
                    return LDAP_ERR_OOB;						/* Out of bounds -- Invalid address */
                memset(hexc, '\0', sizeof(hexc));
                int hlen = snprintf(hexc, sizeof(hexc), "%02X", (int)x);
                strncat(l->search_ip, hexc, hlen);
            } else
                break;								/* reached end of octet */
        } else if (l->status & LDAP_IPV6_S) {
            /* Break down IPv6 address */
            if (swi > 1)
                t = StringSplit(bufb, ':', obj, sizeof(obj));			/* After "::" */
            else
                t = StringSplit(bufa, ':', obj, sizeof(obj));			/* Before "::" */
            /* Convert octet by size (t) - and fill 0's */
            switch (t) {							/* IPv6 is already in HEX, copy contents */
            case 4:
                hexc[0] = (char) toupper((int)obj[0]);
                i = (int)hexc[0];
                if (!isxdigit(i))
                    return LDAP_ERR_OOB;					/* Out of bounds */
                hexc[1] = (char) toupper((int)obj[1]);
                i = (int)hexc[1];
                if (!isxdigit(i))
                    return LDAP_ERR_OOB;					/* Out of bounds */
                hexc[2] = '\0';
                strncat(l->search_ip, hexc, 2);
                hexc[0] = (char) toupper((int)obj[2]);
                i = (int)hexc[0];
                if (!isxdigit(i))
                    return LDAP_ERR_OOB;					/* Out of bounds */
                hexc[1] = (char) toupper((int)obj[3]);
                i = (int)hexc[1];
                if (!isxdigit(i))
                    return LDAP_ERR_OOB;					/* Out of bounds */
                hexc[2] = '\0';
                strncat(l->search_ip, hexc, 2);
                break;
            case 3:
                hexc[0] = '0';
                hexc[1] = (char) toupper((int)obj[0]);
                i = (int)hexc[1];
                if (!isxdigit(i))
                    return LDAP_ERR_OOB;					/* Out of bounds */
                hexc[2] = '\0';
                strncat(l->search_ip, hexc, 2);
                hexc[0] = (char) toupper((int)obj[1]);
                i = (int)hexc[0];
                if (!isxdigit(i))
                    return LDAP_ERR_OOB;					/* Out of bounds */
                hexc[1] = (char) toupper((int)obj[2]);
                i = (int)hexc[1];
                if (!isxdigit(i))
                    return LDAP_ERR_OOB;					/* Out of bounds */
                hexc[2] = '\0';
                strncat(l->search_ip, hexc, 2);
                break;
            case 2:
                strncat(l->search_ip, "00", 2);
                hexc[0] = (char) toupper((int)obj[0]);
                i = (int)hexc[0];
                if (!isxdigit(i))
                    return LDAP_ERR_OOB;					/* Out of bounds */
                hexc[1] = (char) toupper((int)obj[1]);
                i = (int)hexc[1];
                if (!isxdigit(i))
                    return LDAP_ERR_OOB;					/* Out of bounds */
                hexc[2] = '\0';
                strncat(l->search_ip, hexc, 2);
                break;
            case 1:
                strncat(l->search_ip, "00", 2);
                hexc[0] = '0';
                hexc[1] = (char) toupper((int)obj[0]);
                i = (int)hexc[1];
                if (!isxdigit(i))
                    return LDAP_ERR_OOB;					/* Out of bounds */
                hexc[2] = '\0';
                strncat(l->search_ip, hexc, 2);
                break;
            default:
                if (t > 4)
                    return LDAP_ERR_OOB;
                break;
            }
            /* Code to pad the address with 0's between a '::' */
            if ((strlen(bufa) == 0) && (swi == 1)) {
                /* We are *AT* the split, pad in some 0000 */
                t = strlen(bufb);
                /* How many ':' exist in bufb ? */
                j = 0;
                for (i = 0; i < t; ++i) {
                    if (bufb[i] == ':')
                        ++j;
                }
                --j;								/* Preceeding "::" doesn't count */
                t = 8 - (strlen(l->search_ip) / 4) - j;			/* Remainder */
                if (t > 0) {
                    for (i = 0; i < t; ++i)
                        strncat(l->search_ip, "0000", 4);
                }
            }
        }
        if ((bufa[0] == '\0') && (swi > 0)) {
            s = strlen(bufb);
            ++swi;
        } else
            s = strlen(bufa);
    }
    s = strlen(l->search_ip);

    /* CHECK sizes of address, truncate or pad */
    /* if "::" is at end of ip, then pad another block or two */
    while ((l->status & LDAP_IPV6_S) && (s < 32)) {
        strncat(l->search_ip, "0000", 4);
        s = strlen(l->search_ip);
    }
    if ((l->status & LDAP_IPV6_S) && (s > 32)) {
        /* Too long, truncate */
        l->search_ip[32] = '\0';
        s = strlen(l->search_ip);
    }
    /* If at end of ip, and its not long enough, then pad another block or two */
    while ((l->status & LDAP_IPV4_S) && (s < 8)) {
        strncat(l->search_ip, "00", 2);
        s = strlen(l->search_ip);
    }
    if ((l->status & LDAP_IPV4_S) && (s > 8)) {
        /* Too long, truncate */
        l->search_ip[8] = '\0';
        s = strlen(l->search_ip);
    }

    /* Completed, s is length of address in HEX */
    return s;
}