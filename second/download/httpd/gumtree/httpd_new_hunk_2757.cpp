                     "<a href=\"?server\">Server Settings</a>, "
                     "<a href=\"?list\">Module List</a>,  "
                     "<a href=\"?hooks\">Active Hooks</a>", r);
            ap_rputs("</tt></dt></dl><hr />", r);

            ap_rputs("<dl><dt><tt>Sections:<br />", r);
            ap_rputs("<a href=\"#modules\">Loaded Modules</a>, "
                     "<a href=\"#server\">Server Settings</a>, "
                     "<a href=\"#startup_hooks\">Startup Hooks</a>, "
                     "<a href=\"#request_hooks\">Request Hooks</a>, "
                     "<a href=\"#other_hooks\">Other Hooks</a>", r);
            ap_rputs("</tt></dt></dl><hr />", r);

            ap_rputs("<h2><a name=\"modules\">Loaded Modules</a></h2>"
                    "<dl><dt><tt>", r);

            modules = get_sorted_modules(r->pool);
            for (i = 0; i < modules->nelts; i++) {
                modp = APR_ARRAY_IDX(modules, i, module *);
                ap_rprintf(r, "<a href=\"#%s\">%s</a>", modp->name,
                           modp->name);
                if (i < modules->nelts) {
                    ap_rputs(", ", r);
                }
            }
            ap_rputs("</tt></dt></dl><hr />", r);
        }

