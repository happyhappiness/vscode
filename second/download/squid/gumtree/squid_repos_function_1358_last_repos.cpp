void
HttpHdrScTarget::packInto(Packable * p) const
{
    http_hdr_sc_type flag;
    int pcount = 0;
    assert (p);

    for (flag = SC_NO_STORE; flag < SC_ENUM_END; ++flag) {
        if (isSet(flag) && flag != SC_OTHER) {

            /* print option name */
            p->appendf((pcount ? ", %s" : "%s"), ScAttrs[flag].name);

            /* handle options with values */

            if (flag == SC_MAX_AGE)
                p->appendf("=%d", (int) max_age);

            if (flag == SC_CONTENT)
                p->appendf("=\"" SQUIDSTRINGPH "\"", SQUIDSTRINGPRINT(content_));

            ++pcount;
        }
    }

    if (hasTarget())
        p->appendf(";" SQUIDSTRINGPH, SQUIDSTRINGPRINT(target));
}