static apr_status_t socache_shmcb_retrieve(ap_socache_instance_t *ctx, 
                                           server_rec *s, 
                                           const unsigned char *id, unsigned int idlen,
                                           unsigned char *dest, unsigned int *destlen,
                                           apr_pool_t *p)
{
    SHMCBHeader *header = ctx->header;
    SHMCBSubcache *subcache = SHMCB_MASK(header, id);
    int rv;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "socache_shmcb_retrieve (0x%02x -> subcache %d)",
                 SHMCB_MASK_DBG(header, id));

    /* Get the entry corresponding to the id, if it exists. */
    rv = shmcb_subcache_retrieve(s, header, subcache, id, idlen,
                                 dest, destlen);
    if (rv == 0)
        header->stat_retrieves_hit++;
    else
        header->stat_retrieves_miss++;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "leaving socache_shmcb_retrieve successfully");

    return rv == 0 ? APR_SUCCESS : APR_NOTFOUND;
}