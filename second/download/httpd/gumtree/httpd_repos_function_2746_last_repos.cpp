static apr_bucket *h2_beam_bucket(h2_bucket_beam *beam, 
                                  apr_bucket_brigade *dest,
                                  const apr_bucket *src)
{
    apr_bucket *b = NULL;
    int i;
    if (beamers) {
        for (i = 0; i < beamers->nelts && b == NULL; ++i) {
            h2_bucket_beamer *beamer;
            
            beamer = APR_ARRAY_IDX(beamers, i, h2_bucket_beamer*);
            b = beamer(beam, dest, src);
        }
    }
    return b;
}