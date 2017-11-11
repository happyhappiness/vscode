static void dump_vhost_config(apr_file_t *f)
{
    ipaddr_chain *ic;
    int i;

    apr_file_printf(f, "VirtualHost configuration:\n");

    /* non-wildcard servers */
    for (i = 0; i < IPHASH_TABLE_SIZE; ++i) {
        for (ic = iphash_table[i]; ic; ic = ic->next) {
            dump_a_vhost(f, ic);
        }
    }

    /* wildcard servers */
    for (ic = default_list; ic; ic = ic->next) {
        dump_a_vhost(f, ic);
    }
}