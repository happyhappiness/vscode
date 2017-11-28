int
esiEnableProcessing (HttpReply *rep)
{
    int rv = 0;

    if (rep->surrogate_control) {
        HttpHdrScTarget *sctusable = httpHdrScGetMergedTarget (rep->surrogate_control,
                                     Config.Accel.surrogate_id);

        if (!sctusable || sctusable->content.size() == 0)
            /* Nothing generic or targeted at us, or no
             * content processing requested
             */
            return 0;

        if (sctusable->content.pos("ESI/1.0") != NULL)
            rv = 1;

        httpHdrScTargetDestroy (sctusable);
    }

    return rv;
}