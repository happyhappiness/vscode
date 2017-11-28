HttpHdrScTarget *
httpHdrScTargetDup(const HttpHdrScTarget * sc)
{
    HttpHdrScTarget *dup;
    assert(sc);
    dup = httpHdrScTargetCreate(sc->target.termedBuf());
    dup->mask = sc->mask;
    dup->max_age = sc->max_age;
    dup->content = sc->content;
    return dup;
}