static void *merge_magic_server_config(apr_pool_t *p, void *basev, void *addv)
{
    magic_server_config_rec *base = (magic_server_config_rec *) basev;
    magic_server_config_rec *add = (magic_server_config_rec *) addv;
    magic_server_config_rec *new = (magic_server_config_rec *)
                            apr_palloc(p, sizeof(magic_server_config_rec));

    new->magicfile = add->magicfile ? add->magicfile : base->magicfile;
    new->magic = NULL;
    new->last = NULL;
    return new;
}