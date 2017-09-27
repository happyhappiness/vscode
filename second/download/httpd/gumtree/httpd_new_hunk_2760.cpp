                ap_rputs("<p><b>No such module</b></p>\n", r);
            }
        }
    }
    else {
        ap_rputs("<dl><dt>Server Module List</dt>", r);
        modules = get_sorted_modules(r->pool);
        for (i = 0; i < modules->nelts; i++) {
            modp = APR_ARRAY_IDX(modules, i, module *);
            ap_rputs("<dd>", r);
            ap_rputs(modp->name, r);
            ap_rputs("</dd>", r);
        }
        ap_rputs("</dl><hr />", r);
    }
