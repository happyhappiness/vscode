                ap_rputs("<p><b>No such module</b></p>\n", r);
            }
        }
    }
    else {
        ap_rputs("<dl><dt>Server Module List</dt>", r);
        for (modp = ap_top_module; modp; modp = modp->next) {
            ap_rputs("<dd>", r);
            ap_rputs(modp->name, r);
            ap_rputs("</dd>", r);
        }
        ap_rputs("</dl><hr />", r);
    }
