static void socache_mc_status(ap_socache_instance_t *ctx, request_rec *r, int flags)
{
    apr_memcache_t *rc = ctx->mc;
    int i;

    for (i = 0; i < rc->ntotal; i++) {
        apr_memcache_server_t *ms;
        apr_memcache_stats_t *stats;
        apr_status_t rv;
        char *br = (!(flags & AP_STATUS_SHORT) ? "<br />" : "");

        ms = rc->live_servers[i];

        ap_rprintf(r, "Memcached server: %s:%d [%s]%s\n", ms->host, (int)ms->port,
                (ms->status == APR_MC_SERVER_LIVE) ? "Up" : "Down",
                br);
        rv = apr_memcache_stats(ms, r->pool, &stats);
        if (rv != APR_SUCCESS)
            continue;
        if (!(flags & AP_STATUS_SHORT)) {
            ap_rprintf(r, "<b>Version:</b> <i>%s</i> [%u bits], PID: <i>%u</i>, Uptime: <i>%u hrs</i> <br />\n",
                    stats->version , stats->pointer_size, stats->pid, stats->uptime/3600);
            ap_rprintf(r, "<b>Clients::</b> Structures: <i>%u</i>, Total: <i>%u</i>, Current: <i>%u</i> <br />\n",
                    stats->connection_structures, stats->total_connections, stats->curr_connections);
            ap_rprintf(r, "<b>Storage::</b> Total Items: <i>%u</i>, Current Items: <i>%u</i>, Bytes: <i>%" APR_UINT64_T_FMT "</i> <br />\n",
                    stats->total_items, stats->curr_items, stats->bytes);
            ap_rprintf(r, "<b>CPU::</b> System: <i>%u</i>, User: <i>%u</i> <br />\n",
                    (unsigned)stats->rusage_system, (unsigned)stats->rusage_user );
            ap_rprintf(r, "<b>Cache::</b> Gets: <i>%u</i>, Sets: <i>%u</i>, Hits: <i>%u</i>, Misses: <i>%u</i> <br />\n",
                    stats->cmd_get, stats->cmd_set, stats->get_hits, stats->get_misses);
            ap_rprintf(r, "<b>Net::</b> Input bytes: <i>%" APR_UINT64_T_FMT "</i>, Output bytes: <i>%" APR_UINT64_T_FMT "</i> <br />\n",
                    stats->bytes_read, stats->bytes_written);
            ap_rprintf(r, "<b>Misc::</b> Evictions: <i>%" APR_UINT64_T_FMT "</i>, MaxMem: <i>%u</i>, Threads: <i>%u</i> <br />\n",
                    stats->evictions, stats->limit_maxbytes, stats->threads);
            ap_rputs("<hr><br />\n", r);
        }
        else {
            ap_rprintf(r, "Version: %s [%u bits], PID: %u, Uptime: %u hrs %s\n",
                    stats->version , stats->pointer_size, stats->pid, stats->uptime/3600, br);
            ap_rprintf(r, "Clients:: Structures: %d, Total: %d, Current: %u %s\n",
                    stats->connection_structures, stats->total_connections, stats->curr_connections, br);
            ap_rprintf(r, "Storage:: Total Items: %u, Current Items: %u, Bytes: %" APR_UINT64_T_FMT " %s\n",
                    stats->total_items, stats->curr_items, stats->bytes, br);
            ap_rprintf(r, "CPU:: System: %u, User: %u %s\n",
                    (unsigned)stats->rusage_system, (unsigned)stats->rusage_user , br);
            ap_rprintf(r, "Cache:: Gets: %u, Sets: %u, Hits: %u, Misses: %u %s\n",
                    stats->cmd_get, stats->cmd_set, stats->get_hits, stats->get_misses, br);
            ap_rprintf(r, "Net:: Input bytes: %" APR_UINT64_T_FMT ", Output bytes: %" APR_UINT64_T_FMT " %s\n",
                    stats->bytes_read, stats->bytes_written, br);
            ap_rprintf(r, "Misc:: Evictions: %" APR_UINT64_T_FMT ", MaxMem: %u, Threads: %u %s\n",
                    stats->evictions, stats->limit_maxbytes, stats->threads, br);
        }
    }

}