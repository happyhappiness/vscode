bool
HttpHdrCc::parse(const String & str)
{
    const char *item;
    const char *p;		/* '=' parameter */
    const char *pos = NULL;
    http_hdr_cc_type type;
    int ilen;
    int nlen;

    /* iterate through comma separated list */

    while (strListGetItem(&str, ',', &item, &ilen, &pos)) {
        /* isolate directive name */

        if ((p = (const char *)memchr(item, '=', ilen)) && (p - item < ilen)) {
            nlen = p - item;
            ++p;
        } else {
            nlen = ilen;
        }

        /* find type */
        const CcNameToIdMap_t::const_iterator i=CcNameToIdMap.find(StringArea(item,nlen));
        if (i==CcNameToIdMap.end())
            type=CC_OTHER;
        else
            type=i->second;

        // ignore known duplicate directives
        if (isSet(type)) {
            if (type != CC_OTHER) {
                debugs(65, 2, "hdr cc: ignoring duplicate cache-directive: near '" << item << "' in '" << str << "'");
                ++CcAttrs[type].stat.repCount;
                continue;
            }
        }

        /* special-case-parsing and attribute-setting */
        switch (type) {

        case CC_MAX_AGE:
            if (!p || !httpHeaderParseInt(p, &max_age) || max_age < 0) {
                debugs(65, 2, "cc: invalid max-age specs near '" << item << "'");
                clearMaxAge();
            } else {
                setMask(type,true);
            }
            break;

        case CC_S_MAXAGE:
            if (!p || !httpHeaderParseInt(p, &s_maxage) || s_maxage < 0) {
                debugs(65, 2, "cc: invalid s-maxage specs near '" << item << "'");
                clearSMaxAge();
            } else {
                setMask(type,true);
            }
            break;

        case CC_MAX_STALE:
            if (!p || !httpHeaderParseInt(p, &max_stale) || max_stale < 0) {
                debugs(65, 2, "cc: max-stale directive is valid without value");
                maxStale(MAX_STALE_ANY);
            } else {
                setMask(type,true);
            }
            break;

        case CC_MIN_FRESH:
            if (!p || !httpHeaderParseInt(p, &min_fresh) || min_fresh < 0) {
                debugs(65, 2, "cc: invalid min-fresh specs near '" << item << "'");
                clearMinFresh();
            } else {
                setMask(type,true);
            }
            break;

        case CC_STALE_IF_ERROR:
            if (!p || !httpHeaderParseInt(p, &stale_if_error) || stale_if_error < 0) {
                debugs(65, 2, "cc: invalid stale-if-error specs near '" << item << "'");
                clearStaleIfError();
            } else {
                setMask(type,true);
            }
            break;

        case CC_PRIVATE: {
            String temp;
            if (!p)  {
                // Value parameter is optional.
                private_.clean();
            }            else if (/* p &&*/ httpHeaderParseQuotedString(p, (ilen-nlen-1), &temp)) {
                private_.append(temp);
            }            else {
                debugs(65, 2, "cc: invalid private= specs near '" << item << "'");
            }
            // to be safe we ignore broken parameters, but always remember the 'private' part.
            setMask(type,true);
        }
        break;

        case CC_NO_CACHE: {
            String temp;
            if (!p) {
                // On Requests, missing value parameter is expected syntax.
                // On Responses, value parameter is optional.
                setMask(type,true);
                no_cache.clean();
            } else if (/* p &&*/ httpHeaderParseQuotedString(p, (ilen-nlen-1), &temp)) {
                // On Requests, a value parameter is invalid syntax.
                // XXX: identify when parsing request header and dump err message here.
                setMask(type,true);
                no_cache.append(temp);
            } else {
                debugs(65, 2, "cc: invalid no-cache= specs near '" << item << "'");
            }
        }
        break;

        case CC_PUBLIC:
            Public(true);
            break;
        case CC_NO_STORE:
            noStore(true);
            break;
        case CC_NO_TRANSFORM:
            noTransform(true);
            break;
        case CC_MUST_REVALIDATE:
            mustRevalidate(true);
            break;
        case CC_PROXY_REVALIDATE:
            proxyRevalidate(true);
            break;
        case CC_ONLY_IF_CACHED:
            onlyIfCached(true);
            break;

        case CC_OTHER:
            if (other.size())
                other.append(", ");

            other.append(item, ilen);
            break;

        default:
            /* note that we ignore most of '=' specs (RFCVIOLATION) */
            break;
        }
    }

    return (mask != 0);
}