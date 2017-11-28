void
httpHdrScTargetSetMaxAge(HttpHdrScTarget * sc, int max_age)
{
    assert(sc);
    sc->max_age = max_age;

    if (max_age >= 0)
        EBIT_SET(sc->mask, SC_MAX_AGE);
    else
        EBIT_CLR(sc->mask, SC_MAX_AGE);
}