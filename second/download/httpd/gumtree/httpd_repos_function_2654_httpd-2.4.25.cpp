void h2_register_bucket_beamer(h2_bucket_beamer *beamer)
{
    if (!beamers) {
        beamers = apr_array_make(apr_hook_global_pool, 10, 
                                 sizeof(h2_bucket_beamer*));
    }
    APR_ARRAY_PUSH(beamers, h2_bucket_beamer*) = beamer;
}