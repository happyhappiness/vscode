        else {
            apr_file_printf(f, "%8s port * ", "");
        }
        apr_file_printf(f, "namevhost %s (%s:%u)\n",
                        nc->server->server_hostname,
                        nc->server->defn_name, nc->server->defn_line_number);
    }
}

static void dump_vhost_config(apr_file_t *f)
{
    ipaddr_chain *ic;
