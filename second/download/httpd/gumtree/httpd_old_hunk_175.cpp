
    /* just make sure that we are really meant! */
    if (strncmp(r->filename, "redirect:", 9) != 0) {
        return DECLINED;
    }

    /* now do the internal redirect */
    ap_internal_redirect(apr_pstrcat(r->pool, r->filename+9,
                                    r->args ? "?" : NULL, r->args, NULL), r);

    /* and return gracefully */
    return OK;
}


/*
** +-------------------------------------------------------+
** |                                                       |
** |                  the rewriting engine
** |                                                       |
