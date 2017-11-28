void
httpHdrScJoinWith(HttpHdrSc * sc, const HttpHdrSc * new_sc)
{
    assert(sc && new_sc);
#if 0
    /* RC TODO: check that both have the same target */

    if (sc->max_age < 0)
        sc->max_age = new_sc->max_age;

    /* RC TODO: copy unique missing stringlist entries */
    cc->mask |= new_cc->mask;

#endif
}