static int
httpHdrCcParseInit(HttpHdrCc * cc, const String * str)
{
    const char *item;
    const char *p;		/* '=' parameter */
    const char *pos = NULL;
    http_hdr_cc_type type;
    int ilen;
    int nlen;
    assert(cc && str);

    /* iterate through comma separated list */

    while (strListGetItem(str, ',', &item, &ilen, &pos)) {
        /* isolate directive name */

        if ((p = (const char *)memchr(item, '=', ilen)) && (p - item < ilen))
            nlen = p++ - item;
        else
            nlen = ilen;

        /* find type */
        type = (http_hdr_cc_type ) httpHeaderIdByName(item, nlen,
                CcFieldsInfo, CC_ENUM_END);

        if (type < 0) {
            debugs(65, 2, "hdr cc: unknown cache-directive: near '" << item << "' in '" << str << "'");
            type = CC_OTHER;
        }

        // ignore known duplicate directives
        if (EBIT_TEST(cc->mask, type)) {
            if (type != CC_OTHER) {
                debugs(65, 2, "hdr cc: ignoring duplicate cache-directive: near '" << item << "' in '" << str << "'");
                CcFieldsInfo[type].stat.repCount++;
                continue;
            }
        } else {
            EBIT_SET(cc->mask, type);
        }

        /* post-processing special cases */
        switch (type) {

        case CC_MAX_AGE:

            if (!p || !httpHeaderParseInt(p, &cc->max_age)) {
                debugs(65, 2, "cc: invalid max-age specs near '" << item << "'");
                cc->max_age = -1;
                EBIT_CLR(cc->mask, type);
            }

            break;

        case CC_S_MAXAGE:

            if (!p || !httpHeaderParseInt(p, &cc->s_maxage)) {
                debugs(65, 2, "cc: invalid s-maxage specs near '" << item << "'");
                cc->s_maxage = -1;
                EBIT_CLR(cc->mask, type);
            }

            break;

        case CC_MAX_STALE:

            if (!p || !httpHeaderParseInt(p, &cc->max_stale)) {
                debugs(65, 2, "cc: max-stale directive is valid without value");
                cc->max_stale = -1;
            }

            break;

        case CC_MIN_FRESH:

            if (!p || !httpHeaderParseInt(p, &cc->min_fresh)) {
                debugs(65, 2, "cc: invalid min-fresh specs near '" << item << "'");
                cc->min_fresh = -1;
                EBIT_CLR(cc->mask, type);
            }

            break;

        case CC_STALE_IF_ERROR:
            if (!p || !httpHeaderParseInt(p, &cc->stale_if_error)) {
                debugs(65, 2, "cc: invalid stale-if-error specs near '" << item << "'");
                cc->stale_if_error = -1;
                EBIT_CLR(cc->mask, type);
            }
            break;

        case CC_OTHER:

            if (cc->other.size())
                cc->other.append(", ");

            cc->other.append(item, ilen);

            break;

        default:
            /* note that we ignore most of '=' specs (RFCVIOLATION) */
            break;
        }
    }

    return cc->mask != 0;
}