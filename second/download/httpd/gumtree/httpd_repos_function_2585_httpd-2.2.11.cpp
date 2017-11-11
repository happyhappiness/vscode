static apr_status_t write_page(apr_sdbm_t *db, const char *buf, long pagno)
{
    apr_status_t status;
    apr_off_t off = OFF_PAG(pagno);
    
    if ((status = apr_file_seek(db->pagf, APR_SET, &off)) == APR_SUCCESS)
        status = apr_file_write_full(db->pagf, buf, PBLKSIZ, NULL);

    return status;
}