        while (modp && modp->next != m) {
            modp = modp->next;
        }

        if (!modp) {
            /* Uh-oh, this module doesn't exist */
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                         "Cannot remove module %s: not found in module list",
                         m->name);
            return;
        }

        /* Eliminate us from the module list */
