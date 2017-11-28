void
HttpHdrScTarget::packInto(Packer * p) const
{
    http_hdr_sc_type flag;
    int pcount = 0;
    assert (p);

    for (flag = SC_NO_STORE; flag < SC_ENUM_END; ++flag) {
        if (isSet(flag) && flag != SC_OTHER) {

            /* print option name */
            packerPrintf(p, (pcount ? ", " SQUIDSTRINGPH : SQUIDSTRINGPH),
                         SQUIDSTRINGPRINT(ScFieldsInfo[flag].name));

            /* handle options with values */

            if (flag == SC_MAX_AGE)
                packerPrintf(p, "=%d", (int) max_age);

            if (flag == SC_CONTENT)
                packerPrintf(p, "=\"" SQUIDSTRINGPH "\"", SQUIDSTRINGPRINT(content_));

            ++pcount;
        }
    }

    if (hasTarget())
        packerPrintf (p, ";" SQUIDSTRINGPH, SQUIDSTRINGPRINT(target));
}