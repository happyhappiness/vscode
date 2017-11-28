void
httpHdrScTargetMergeWith(HttpHdrScTarget * sc, const HttpHdrScTarget * new_sc)
{
    http_hdr_sc_type c;
    assert(sc && new_sc);
    /* Don't touch the target - this is used to get the operations for a
     * single surrogate
     */

    for (c = SC_NO_STORE; c < SC_ENUM_END; ++c)
        if (!EBIT_TEST(sc->mask, c) && EBIT_TEST(new_sc->mask,c)) {
            EBIT_SET(sc->mask, c);

            switch (c) {

            case SC_MAX_AGE:
                sc->max_age = new_sc->max_age;
                sc->max_stale = new_sc->max_stale;
                break;

            case SC_CONTENT:
                assert (sc->content.size() == 0);
                sc->content = new_sc->content;
                break;

            default:
                break;
            }
        }
}