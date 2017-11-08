static int find_list_item(apr_pool_t *p, const char *line,
                                  const char *tok, ap_etag_e type)
{
    const unsigned char *pos;
    const unsigned char *ptr = (const unsigned char *)line;
    int good = 0, addspace = 0, in_qpair = 0, in_qstr = 0, in_com = 0;

    if (!line || !tok) {
        return 0;
    }
    if (type == AP_ETAG_STRONG && *tok != '\"') {
        return 0;
    }
    if (type == AP_ETAG_WEAK) {
        if (*tok == 'W' && (*(tok+1)) == '/' && (*(tok+2)) == '\"') {
            tok += 2;
        }
        else if (*tok != '\"') {
            return 0;
        }
    }

    do {  /* loop for each item in line's list */

        /* Find first non-comma, non-whitespace byte */
        while (*ptr == ',' || apr_isspace(*ptr)) {
            ++ptr;
        }

        /* Account for strong or weak Etags, depending on our search */
        if (type == AP_ETAG_STRONG && *ptr != '\"') {
            break;
        }
        if (type == AP_ETAG_WEAK) {
            if (*ptr == 'W' && (*(ptr+1)) == '/' && (*(ptr+2)) == '\"') {
                ptr += 2;
            }
            else if (*ptr != '\"') {
                break;
            }
        }

        if (*ptr)
            good = 1;  /* until proven otherwise for this item */
        else
            break;     /* no items left and nothing good found */

        /* We skip extra whitespace and any whitespace around a '=', '/',
         * or ';' and lowercase normal characters not within a comment,
         * quoted-string or quoted-pair.
         */
        for (pos = (const unsigned char *)tok;
             *ptr && (in_qpair || in_qstr || in_com || *ptr != ',');
             ++ptr) {

            if (in_qpair) {
                in_qpair = 0;
                if (good)
                    good = (*pos++ == *ptr);
            }
            else {
                switch (*ptr) {
                    case '\\': in_qpair = 1;
                               if (addspace == 1)
                                   good = good && (*pos++ == ' ');
                               good = good && (*pos++ == *ptr);
                               addspace = 0;
                               break;
                    case '"' : if (!in_com)
                                   in_qstr = !in_qstr;
                               if (addspace == 1)
                                   good = good && (*pos++ == ' ');
                               good = good && (*pos++ == *ptr);
                               addspace = 0;
                               break;
                    case '(' : if (!in_qstr)
                                   ++in_com;
                               if (addspace == 1)
                                   good = good && (*pos++ == ' ');
                               good = good && (*pos++ == *ptr);
                               addspace = 0;
                               break;
                    case ')' : if (in_com)
                                   --in_com;
                               good = good && (*pos++ == *ptr);
                               addspace = 0;
                               break;
                    case ' ' :
                    case '\t': if (addspace || !good)
                                   break;
                               if (in_com || in_qstr)
                                   good = (*pos++ == *ptr);
                               else
                                   addspace = 1;
                               break;
                    case '=' :
                    case '/' :
                    case ';' : if (!(in_com || in_qstr))
                                   addspace = -1;
                               good = good && (*pos++ == *ptr);
                               break;
                    default  : if (!good)
                                   break;
                               if (addspace == 1)
                                   good = (*pos++ == ' ');
                               if (in_com || in_qstr)
                                   good = good && (*pos++ == *ptr);
                               else
                                   good = good
                                       && (apr_tolower(*pos++) == apr_tolower(*ptr));
                               addspace = 0;
                               break;
                }
            }
        }
        if (good && *pos)
            good = 0;          /* not good if only a prefix was matched */

    } while (*ptr && !good);

    return good;
}