apr_status_t apr_dir_rewind(apr_dir_t *thedir)
{
    rewinddir(thedir->dirstruct);
    return APR_SUCCESS;
}