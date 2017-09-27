                                           -1 : b->length));
            }
        }
        line = *buffer? buffer : "(empty)";
    }
    /* Intentional no APLOGNO */
    ap_log_cerror(APLOG_MARK, level, 0, c, "h2_session(%ld)-%s: %s", 
                  c->id, tag, line);

}

apr_status_t h2_conn_io_init(h2_conn_io *io, conn_rec *c, 
                             const h2_config *cfg)
{
    io->c              = c;
    io->output         = apr_brigade_create(c->pool, c->bucket_alloc);
    io->is_tls         = h2_h2_is_tls(c);
    io->buffer_output  = io->is_tls;
    io->flush_threshold = (apr_size_t)h2_config_geti64(cfg, H2_CONF_STREAM_MAX_MEM);

    if (io->is_tls) {
        /* This is what we start with, 
         * see https://issues.apache.org/jira/browse/TS-2503 
         */
        io->warmup_size    = h2_config_geti64(cfg, H2_CONF_TLS_WARMUP_SIZE);
        io->cooldown_usecs = (h2_config_geti(cfg, H2_CONF_TLS_COOLDOWN_SECS) 
