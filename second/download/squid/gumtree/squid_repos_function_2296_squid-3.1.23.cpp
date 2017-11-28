void
httpHdrCcPackInto(const HttpHdrCc * cc, Packer * p)
{
    http_hdr_cc_type flag;
    int pcount = 0;
    assert(cc && p);

    for (flag = CC_PUBLIC; flag < CC_ENUM_END; ++flag) {
        if (EBIT_TEST(cc->mask, flag) && flag != CC_OTHER) {

            /* print option name */
            packerPrintf(p, (pcount ? ", " SQUIDSTRINGPH : SQUIDSTRINGPH),
                         SQUIDSTRINGPRINT(CcFieldsInfo[flag].name));

            /* handle options with values */

            if (flag == CC_MAX_AGE)
                packerPrintf(p, "=%d", (int) cc->max_age);

            if (flag == CC_S_MAXAGE)
                packerPrintf(p, "=%d", (int) cc->s_maxage);

            if (flag == CC_MAX_STALE && cc->max_stale >= 0)
                packerPrintf(p, "=%d", (int) cc->max_stale);

            if (flag == CC_MIN_FRESH)
                packerPrintf(p, "=%d", (int) cc->min_fresh);

            pcount++;
        }
    }

    if (cc->other.size() != 0)
        packerPrintf(p, (pcount ? ", " SQUIDSTRINGPH : SQUIDSTRINGPH),
                     SQUIDSTRINGPRINT(cc->other));
}