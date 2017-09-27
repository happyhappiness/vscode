
static void store_slotmem(ap_slotmem_instance_t *slotmem)
{
    apr_file_t *fp;
    apr_status_t rv;
    apr_size_t nbytes;
    unsigned char digest[APR_MD5_DIGESTSIZE];
    const char *storename = slotmem->pname;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02334)
                 "storing %s", storename);

    if (storename) {
        rv = apr_file_open(&fp, storename, APR_CREATE | APR_READ | APR_WRITE,
