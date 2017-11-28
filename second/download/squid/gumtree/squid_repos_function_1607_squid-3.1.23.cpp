void
httpHdrScTargetPackInto(const HttpHdrScTarget * sc, Packer * p)
{
    http_hdr_sc_type flag;
    int pcount = 0;
    assert(sc && p);

    for (flag = SC_NO_STORE; flag < SC_ENUM_END; ++flag) {
        if (EBIT_TEST(sc->mask, flag) && flag != SC_OTHER) {

            /* print option name */
            packerPrintf(p, (pcount ? ", " SQUIDSTRINGPH : SQUIDSTRINGPH),
                         SQUIDSTRINGPRINT(ScFieldsInfo[flag].name));

            /* handle options with values */

            if (flag == SC_MAX_AGE)
                packerPrintf(p, "=%d", (int) sc->max_age);

            if (flag == SC_CONTENT)
                packerPrintf(p, "=\"" SQUIDSTRINGPH "\"", SQUIDSTRINGPRINT(sc->content));

            pcount++;
        }
    }

    if (sc->target.size())
        packerPrintf (p, ";" SQUIDSTRINGPH, SQUIDSTRINGPRINT(sc->target));
}