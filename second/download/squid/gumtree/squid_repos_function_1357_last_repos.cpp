bool
HttpHdrSc::parse(const String * str)
{
    HttpHdrSc * sc=this;
    const char *item;
    const char *p;      /* '=' parameter */
    const char *pos = NULL;
    const char *target = NULL; /* ;foo */
    const char *temp = NULL; /* temp buffer */
    http_hdr_sc_type type;
    int ilen, vlen;
    int initiallen;
    HttpHdrScTarget *sct;
    assert(str);

    /* iterate through comma separated list */

    while (strListGetItem(str, ',', &item, &ilen, &pos)) {
        initiallen = ilen;
        vlen = 0;
        /* decrease ilen to still match the token for  '=' statements */

        if ((p = strchr(item, '=')) && (p - item < ilen)) {
            vlen = ilen - (p + 1 - item);
            ilen = p - item;
            ++p;
        }

        /* decrease ilen to still match the token for ';' qualified non '=' statments */
        else if ((p = strchr(item, ';')) && (p - item < ilen)) {
            ilen = p - item;
            ++p;
        }

        /* find type */
        type = scLookupTable.lookup(SBuf(item,ilen));

        if (type == SC_ENUM_END) {
            debugs(90, 2, "hdr sc: unknown control-directive: near '" << item << "' in '" << str << "'");
            type = SC_OTHER;
        }

        /* Is this a targeted directive? */
        /* TODO: remove the temporary useage and use memrchr and the information we have instead */
        temp = xstrndup (item, initiallen + 1);

        if (!((target = strrchr (temp, ';')) && !strchr (target, '"') && *(target + 1) != '\0'))
            target = NULL;
        else
            ++target;

        sct = sc->findTarget(target);

        if (!sct) {
            sct = new HttpHdrScTarget(target);
            addTarget(sct);
        }

        safe_free (temp);

        if (sct->isSet(type)) {
            if (type != SC_OTHER)
                debugs(90, 2, "hdr sc: ignoring duplicate control-directive: near '" << item << "' in '" << str << "'");

            ++ scHeaderStats[type].repCount;

            continue;
        }

        /* process directives */
        switch (type) {
        case SC_NO_STORE:
            sct->noStore(true);
            break;

        case SC_NO_STORE_REMOTE:
            sct->noStoreRemote(true);
            break;

        case SC_MAX_AGE: {
            int ma;
            if (p && httpHeaderParseInt(p, &ma)) {
                sct->maxAge(ma);

                if ((p = strchr (p, '+'))) {
                    int ms;
                    ++p; //skip the + char
                    if (httpHeaderParseInt(p, &ms)) {
                        sct->maxStale(ms);
                    } else {
                        debugs(90, 2, "sc: invalid max-stale specs near '" << item << "'");
                        sct->clearMaxStale();
                        /* leave the max-age alone */
                    }
                }
            } else {
                debugs(90, 2, "sc: invalid max-age specs near '" << item << "'");
                sct->clearMaxAge();
            }

            break;
        }

        case SC_CONTENT:

            if ( p && httpHeaderParseQuotedString(p, vlen, &sct->content_)) {
                sct->setMask(SC_CONTENT,true); // ugly but saves a copy
            } else {
                debugs(90, 2, "sc: invalid content= quoted string near '" << item << "'");
                sct->clearContent();
            }
            break;

        case SC_OTHER:
        default:
            break;
        }
    }

    return sc->targets.head != NULL;
}