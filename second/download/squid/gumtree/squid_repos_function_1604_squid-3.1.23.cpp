static int
httpHdrScParseInit(HttpHdrSc * sc, const String * str)
{
    const char *item;
    const char *p;		/* '=' parameter */
    const char *pos = NULL;
    const char *target = NULL; /* ;foo */
    const char *temp = NULL; /* temp buffer */
    int type;
    int ilen;
    int initiallen;
    HttpHdrScTarget *sct;
    assert(sc && str);

    /* iterate through comma separated list */

    while (strListGetItem(str, ',', &item, &ilen, &pos)) {
        initiallen = ilen;
        /* decrease ilen to still match the token for  '=' statements */

        if ((p = strchr(item, '=')) && (p - item < ilen))
            ilen = p++ - item;

        /* decrease ilen to still match the token for ';' qualified non '=' statments */
        else if ((p = strchr(item, ';')) && (p - item < ilen))
            ilen = p++ - item;

        /* find type */
        type = httpHeaderIdByName(item, ilen,
                                  ScFieldsInfo, SC_ENUM_END);

        if (type < 0) {
            debugs(90, 2, "hdr sc: unknown control-directive: near '" << item << "' in '" << str << "'");
            type = SC_OTHER;
        }

        /* Is this a targeted directive? */
        /* TODO sometime: implement a strnrchr that looks at a substring */
        temp = xstrndup (item, initiallen + 1);

        if (!((target = strrchr (temp, ';')) && !strchr (target, '"') && *(target + 1) != '\0'))
            target = NULL;
        else
            ++target;

        sct = httpHdrScFindTarget (sc, target);

        if (!sct) {
            sct = httpHdrScTargetCreate (target);
            dlinkAdd(sct, &sct->node, &sc->targets);
        }

        safe_free (temp);

        if (EBIT_TEST(sct->mask, type)) {
            if (type != SC_OTHER)
                debugs(90, 2, "hdr sc: ignoring duplicate control-directive: near '" << item << "' in '" << str << "'");

            ScFieldsInfo[type].stat.repCount++;

            continue;
        }

        /* update mask */
        EBIT_SET(sct->mask, type);

        /* post-processing special cases */
        switch (type) {

        case SC_MAX_AGE:

            if (!p || !httpHeaderParseInt(p, &sct->max_age)) {
                debugs(90, 2, "sc: invalid max-age specs near '" << item << "'");
                sct->max_age = -1;
                EBIT_CLR(sct->mask, type);
            }

            if ((p = strchr (p, '+')))
                if (!httpHeaderParseInt(++p, &sct->max_stale)) {
                    debugs(90, 2, "sc: invalid max-stale specs near '" << item << "'");
                    sct->max_stale = 0;
                    /* leave the max-age alone */
                }

            break;

        case SC_CONTENT:

            if (!p || !httpHeaderParseQuotedString(p, &sct->content)) {
                debugs(90, 2, "sc: invalid content= quoted string near '" << item << "'");
                sct->content.clean();
                EBIT_CLR(sct->mask, type);
            }

        default:
            break;
        }
    }

    return sc->targets.head != NULL;
}