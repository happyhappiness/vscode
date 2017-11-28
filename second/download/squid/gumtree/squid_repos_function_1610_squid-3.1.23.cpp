void
httpHdrScSetMaxAge(HttpHdrSc * sc, char const *target, int max_age)
{
    HttpHdrScTarget *sct;
    assert(sc);
    sct = httpHdrScFindTarget (sc, target);

    if (!sct) {
        sct = httpHdrScTargetCreate (target);
        dlinkAddTail (sct, &sct->node, &sc->targets);
    }

    httpHdrScTargetSetMaxAge(sct, max_age);
}