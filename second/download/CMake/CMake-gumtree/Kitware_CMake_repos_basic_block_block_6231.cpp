f(HTTPREQ_HEAD == data->set.httpreq)
    /* ... but if unset there really is no perfect method that is the
       "opposite" of HEAD but in reality most people probably think GET
       then. The important thing is that we can't let it remain HEAD if the
       opt_no_body is set FALSE since then we'll behave wrong when getting
       HTTP. */
    data->set.httpreq = HTTPREQ_GET