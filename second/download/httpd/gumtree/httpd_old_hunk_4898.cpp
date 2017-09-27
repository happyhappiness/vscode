 * none      : no persistent data
 * rel_name  : $server_root/rel_name
 * /abs_name : $abs_name
 *
 */

static const char *slotmem_filename(apr_pool_t *pool, const char *slotmemname)
{
    const char *fname;
    if (!slotmemname || strcasecmp(slotmemname, "none") == 0) {
        return NULL;
    }
    else if (slotmemname[0] != '/') {
        const char *filenm = apr_pstrcat(pool, DEFAULT_SLOTMEM_PREFIX,
                                       slotmemname, DEFAULT_SLOTMEM_SUFFIX, NULL);
        fname = ap_runtime_dir_relative(pool, filenm);
    }
    else {
        fname = slotmemname;
    }
    return fname;
}

static void store_slotmem(ap_slotmem_instance_t *slotmem)
{
    apr_file_t *fp;
    apr_status_t rv;
    apr_size_t nbytes;
    const char *storename;

    storename = slotmem_filename(slotmem->gpool, slotmem->name);

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
        nbytes = (slotmem->desc.size * slotmem->desc.num) +
                 (slotmem->desc.num * sizeof(char)) + AP_UNSIGNEDINT_OFFSET;
        apr_file_write(fp, slotmem->persist, &nbytes);
        apr_file_close(fp);
    }
}

/* should be apr_status_t really */
static void restore_slotmem(void *ptr, const char *name, apr_size_t size,
