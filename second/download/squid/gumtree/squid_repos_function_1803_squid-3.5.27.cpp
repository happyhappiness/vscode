HttpHdrScTarget *
HttpHdrSc::getMergedTarget(const char *ourtarget)
{
    HttpHdrScTarget *sctus = findTarget(ourtarget);
    HttpHdrScTarget *sctgeneric = findTarget(NULL);

    if (sctgeneric || sctus) {
        HttpHdrScTarget *sctusable = new HttpHdrScTarget(NULL);

        if (sctgeneric)
            sctusable->mergeWith(sctgeneric);

        if (sctus)
            sctusable->mergeWith(sctus);

        return sctusable;
    }

    return NULL;
}