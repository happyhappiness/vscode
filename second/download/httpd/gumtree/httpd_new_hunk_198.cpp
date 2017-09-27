		       "<tt>Max Daemons: %d Threaded: %s Forked: %s</tt></dt>\n",
                       max_daemons, threaded ? "yes" : "no",
                       forked ? "yes" : "no");
            ap_rprintf(r, "<dt><strong>Server Root:</strong> "
                        "<tt>%s</tt></dt>\n", ap_server_root);
            ap_rprintf(r, "<dt><strong>Config File:</strong> "
		       "<tt>%s</tt></dt>\n", ap_conftree->filename);
            ap_rputs("</dl><hr />", r);
        }
        for (modp = ap_top_module; modp; modp = modp->next) {
            if (!r->args || !strcasecmp(modp->name, r->args)) {
                ap_rprintf(r, "<dl><dt><a name=\"%s\"><strong>Module Name:</strong> "
                            "<font size=\"+1\"><tt>%s</tt></font></a></dt>\n",
