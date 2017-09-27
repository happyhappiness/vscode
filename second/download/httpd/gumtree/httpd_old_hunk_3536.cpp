

AP_DECLARE_NONSTD(const char *)ap_set_name_virtual_host(cmd_parms *cmd,
                                                        void *dummy,
                                                        const char *arg)
{
    /* use whatever port the main server has at this point */
    return get_addresses(cmd->pool, arg, &name_vhost_list_tail,
                         cmd->server->port);
}


/* hash table statistics, keep this in here for the beta period so
 * we can find out if the hash function is ok
 */
