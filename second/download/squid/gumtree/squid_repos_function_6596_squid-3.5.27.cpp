int
esiEnableProcessing (HttpReply *rep)
{
    int rv = 0;

    if (rep->surrogate_control) {
        HttpHdrScTarget *sctusable =
            rep->surrogate_control->getMergedTarget(Config.Accel.surrogate_id);

        // found something targeted at us
        if (sctusable &&
                sctusable->hasContent() &&
                sctusable->content().pos("ESI/1.0")) {
            rv = 1;
        }

        delete sctusable;
    }

    return rv;
}