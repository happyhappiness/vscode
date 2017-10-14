static apr_status_t socache_shmcb_remove(ap_socache_instance_t *ctx, 
                                         server_rec *s, const unsigned char *id,
                                         unsigned int idlen, apr_pool_t *p)
{
    SHMCBHeader *header = ctx->header;
    SHMCBSubcache *subcache = SHMCB_MASK(header, id);
    apr_status_t rv;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "socache_shmcb_remove (0x%02x -> subcache %d)",
                 SHMCB_MASK_DBG(header, id));
    if (idlen < 4) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "unusably short id provided "
                "(%u bytes)", idlen);
        return APR_EINVAL;
    }
    if (shmcb_subcache_remove(s, header, subcache, id, idlen) == 0) {
        header->stat_removes_hit++;
        rv = APR_SUCCESS;
    } else {
        header->stat_removes_miss++;
        rv = APR_NOTFOUND;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving socache_shmcb_remove successfully");

    return rv;
}