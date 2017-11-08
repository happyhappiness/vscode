void dav_fs_register(apr_pool_t *p)
{
    /* register the namespace URIs */
    dav_register_liveprop_group(p, &dav_fs_liveprop_group);

    /* register the repository provider */
    dav_register_provider(p, "filesystem", &dav_fs_provider);
}