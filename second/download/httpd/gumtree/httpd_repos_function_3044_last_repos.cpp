static void *create_server_config(apr_pool_t *p, server_rec *s)
{
    brotli_server_config_t *conf = apr_pcalloc(p, sizeof(*conf));

    /* These default values allow mod_brotli to behave similarly to
     * mod_deflate in terms of compression speed and memory usage.
     *
     * The idea is that since Brotli (generally) gives better compression
     * ratio than Deflate, simply enabling mod_brotli on the server
     * will reduce the amount of transferred data while keeping everything
     * else unchanged.  See https://quixdb.github.io/squash-benchmark/
     */
    conf->quality = 5;
    conf->lgwin = 18;
    /* Zero is a special value for BROTLI_PARAM_LGBLOCK that allows
     * Brotli to automatically select the optimal input block size based
     * on other encoder parameters.  See enc/quality.h: ComputeLgBlock().
     */
    conf->lgblock = 0;
    conf->etag_mode = ETAG_MODE_ADDSUFFIX;

    return conf;
}