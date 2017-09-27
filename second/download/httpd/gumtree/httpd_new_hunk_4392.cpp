            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                          APLOGNO(03057)
                          "h2_session(%ld): push diary set from Cache-Digest: %s", 
                          session->id, cache_digest);
        }
    }
    pushes = h2_push_collect(stream->pool, req, stream->push_policy, res);
    return h2_push_diary_update(stream->session, pushes);
}

static apr_int32_t h2_log2inv(unsigned char log2)
{
    return log2? (1 << log2) : 1;
}


typedef struct {
    h2_push_diary *diary;
    unsigned char log2p;
    int mask_bits;
    int delta_bits;
    int fixed_bits;
    apr_uint64_t fixed_mask;
    apr_pool_t *pool;
    unsigned char *data;
    apr_size_t datalen;
    apr_size_t offset;
    unsigned int bit;
