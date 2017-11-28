void
HttpStateData::processSurrogateControl(HttpReply *reply)
{
#if USE_SQUID_ESI

    if (request->flags.accelerated && reply->surrogate_control) {
        HttpHdrScTarget *sctusable =
            httpHdrScGetMergedTarget(reply->surrogate_control,
                                     Config.Accel.surrogate_id);

        if (sctusable) {
            if (EBIT_TEST(sctusable->mask, SC_NO_STORE) ||
                    (Config.onoff.surrogate_is_remote
                     && EBIT_TEST(sctusable->mask, SC_NO_STORE_REMOTE))) {
                surrogateNoStore = true;
                entry->makePrivate();
            }

            /* The HttpHeader logic cannot tell if the header it's parsing is a reply to an
             * accelerated request or not...
             * Still, this is an abtraction breach. - RC
             */
            if (sctusable->max_age != -1) {
                if (sctusable->max_age < sctusable->max_stale)
                    reply->expires = reply->date + sctusable->max_age;
                else
                    reply->expires = reply->date + sctusable->max_stale;

                /* And update the timestamps */
                entry->timestampsSet();
            }

            /* We ignore cache-control directives as per the Surrogate specification */
            ignoreCacheControl = true;

            httpHdrScTargetDestroy(sctusable);
        }
    }

#endif
}