static apr_status_t read_heartbeats(const char *path, apr_hash_t *servers,
                                        apr_pool_t *pool)
{
    apr_status_t rv;
    if (hm_serversmem) {
        ctx_servers_t ctx;
        ctx.now = apr_time_now();
        ctx.servers = servers;
        rv = readslot_heartbeats(&ctx, pool);
    } else
        rv = readfile_heartbeats(path, servers, pool);
    return rv;
}