static void *dbd_oracle_native(apr_dbd_t *handle)
{
    /* FIXME: can we do anything better?  Oracle doesn't seem to have
     * a concept of a handle in the sense we use it.
     */
    return dbd_oracle_env;
}