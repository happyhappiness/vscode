static void store_slotmem(ap_slotmem_instance_t *slotmem)
{
    apr_file_t *fp;
    apr_status_t rv;
    apr_size_t nbytes;
    const char *storename;

    storename = slotmem_filename(slotmem->gpool, slotmem->name, 1);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02334)
                 "storing %s", storename);

    if (storename) {
        rv = apr_file_open(&fp, storename, APR_CREATE | APR_READ | APR_WRITE,
                           APR_OS_DEFAULT, slotmem->gpool);
        if (APR_STATUS_IS_EEXIST(rv)) {
            apr_file_remove(storename, slotmem->gpool);
            rv = apr_file_open(&fp, storename, APR_CREATE | APR_READ | APR_WRITE,
                               APR_OS_DEFAULT, slotmem->gpool);
        }
        if (rv != APR_SUCCESS) {
            return;
        }
        if (AP_SLOTMEM_IS_CLEARINUSE(slotmem)) {
            slotmem_clearinuse(slotmem);
        }
        nbytes = (slotmem->desc.size * slotmem->desc.num) +
                 (slotmem->desc.num * sizeof(char)) + AP_UNSIGNEDINT_OFFSET;
        /* XXX: Error handling */
        apr_file_write_full(fp, slotmem->persist, nbytes, NULL);
        apr_file_close(fp);
    }
}