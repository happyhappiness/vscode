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

static void dump_vhost_config(apr_file_t *f)
{
    ipaddr_chain *ic;
