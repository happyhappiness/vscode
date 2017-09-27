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
        modp->next = modp->next->next;
    }

    free(ap_module_short_names[m->module_index]);
    ap_module_short_names[m->module_index] = NULL;

    m->module_index = -1; /* simulate being unloaded, should
                           * be unnecessary */
    dynamic_modules--;
    total_modules--;
}
