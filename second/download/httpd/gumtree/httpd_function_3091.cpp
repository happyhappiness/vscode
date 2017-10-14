static void dump_a_vhost(apr_file_t *f, ipaddr_chain *ic)
{
    name_chain *nc;
    int len;
    char buf[MAX_STRING_LEN];
    apr_sockaddr_t *ha = ic->sar->host_addr;

    if (ha->family == APR_INET &&
        ha->sa.sin.sin_addr.s_addr == DEFAULT_VHOST_ADDR) {
        len = apr_snprintf(buf, sizeof(buf), "_default_:%u",
                           ic->sar->host_port);
    }
    else if (ha->family == APR_INET &&
             ha->sa.sin.sin_addr.s_addr == INADDR_ANY) {
        len = apr_snprintf(buf, sizeof(buf), "*:%u",
                           ic->sar->host_port);
    }
    else {
        len = apr_snprintf(buf, sizeof(buf), "%pI", ha);
    }
    if (ic->sar->host_port == 0) {
        buf[len-1] = '*';
    }
    if (ic->names == NULL) {
        apr_file_printf(f, "%-22s %s (%s:%u)\n", buf,
                        ic->server->server_hostname,
                        ic->server->defn_name, ic->server->defn_line_number);
        return;
    }
    apr_file_printf(f, "%-22s is a NameVirtualHost\n"
                    "%8s default server %s (%s:%u)\n",
                    buf, "", ic->server->server_hostname,
                    ic->server->defn_name, ic->server->defn_line_number);
    for (nc = ic->names; nc; nc = nc->next) {
        if (nc->sar->host_port) {
            apr_file_printf(f, "%8s port %u ", "", nc->sar->host_port);
        }
        else {
            apr_file_printf(f, "%8s port * ", "");
        }
        apr_file_printf(f, "namevhost %s (%s:%u)\n",
                        nc->server->server_hostname,
                        nc->server->defn_name, nc->server->defn_line_number);
        if (nc->server->names) {
            apr_array_header_t *names = nc->server->names;
            char **name = (char **)names->elts;
            int i;
            for (i = 0; i < names->nelts; ++i) {
                if (name[i]) {
                    apr_file_printf(f, "%16s alias %s\n", "", name[i]);
                }
            }
        }
        if (nc->server->wild_names) {
            apr_array_header_t *names = nc->server->wild_names;
            char **name = (char **)names->elts;
            int i;
            for (i = 0; i < names->nelts; ++i) {
                if (name[i]) {
                    apr_file_printf(f, "%16s wild alias %s\n", "", name[i]);
                }
            }
        }
    }
}