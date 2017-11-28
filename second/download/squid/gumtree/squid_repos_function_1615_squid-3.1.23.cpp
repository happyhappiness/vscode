HttpHdrScTarget *
httpHdrScGetMergedTarget (HttpHdrSc *sc, const char *ourtarget)
{
    HttpHdrScTarget *sctus = httpHdrScFindTarget (sc, ourtarget);
    HttpHdrScTarget *sctgeneric = httpHdrScFindTarget (sc, NULL);

    if (sctgeneric || sctus) {
        HttpHdrScTarget *sctusable = httpHdrScTargetCreate (NULL);

        if (sctgeneric)
            httpHdrScTargetMergeWith (sctusable, sctgeneric);

        if (sctus)
            httpHdrScTargetMergeWith (sctusable, sctus);

        return sctusable;
    }

    return NULL;
}