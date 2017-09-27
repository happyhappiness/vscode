                     "<a href=\"?server\">Server Settings</a>, "
                     "<a href=\"?list\">Module List</a>,  "
                     "<a href=\"?hooks\">Active Hooks</a>", r);
            ap_rputs("</tt></dt></dl><hr />", r);

            ap_rputs("<dl><dt><tt>Sections:<br />", r);
            ap_rputs("<a href=\"#server\">Server Settings</a>, "
                     "<a href=\"#startup_hooks\">Startup Hooks</a>, "
                     "<a href=\"#request_hooks\">Request Hooks</a>", r);
            ap_rputs("</tt></dt></dl><hr />", r);

            ap_rputs("<dl><dt><tt>Loaded Modules: <br />", r);
            /* TODO: Sort by Alpha */
            for (modp = ap_top_module; modp; modp = modp->next) {
                ap_rprintf(r, "<a href=\"#%s\">%s</a>", modp->name,
                           modp->name);
                if (modp->next) {
                    ap_rputs(", ", r);
                }
            }
            ap_rputs("</tt></dt></dl><hr />", r);
        }

