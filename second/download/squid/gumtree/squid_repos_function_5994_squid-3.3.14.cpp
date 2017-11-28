int
esiEnableProcessing (HttpReply *rep)
{
    int rv = 0;

    if (rep->surrogate_control) {
        HttpHdrScTarget *sctusable =
            rep->surrogate_control->getMergedTarget(Config.Accel.surrogate_id);

        if (!sctusable || !sctusable->hasContent())
            /* Nothing generic or targeted at us, or no
             * content processing requested
             */
            return 0;

        if (sctusable->content().pos("ESI/1.0") != NULL)
            rv = 1;

        delete sctusable;
    }

    return rv;
}