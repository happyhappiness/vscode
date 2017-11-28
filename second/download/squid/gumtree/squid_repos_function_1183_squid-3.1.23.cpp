void
httpHdrScTargetJoinWith(HttpHdrScTarget * sc, const HttpHdrScTarget * new_sc)
{
    assert(sc && new_sc);
    /* TODO: check both targets are the same */

    if (sc->max_age < 0)
        sc->max_age = new_sc->max_age;

    if (sc->max_stale < new_sc->max_stale)
        sc->max_stale = new_sc->max_stale;

    /* RC TODO: copy unique missing content stringlist entries */
    sc->mask |= new_sc->mask;
}