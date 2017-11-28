HttpHdrScTarget *
httpHdrScTargetCreate(char const *target)
{
    HttpHdrScTarget *sc = new HttpHdrScTarget();
    sc->max_age = -1;
    /* max_stale is specified as 0 if not specified in the header */
    sc->target = target;
    return sc;
}