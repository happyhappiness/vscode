
    if (err->desc != NULL) {
        /* ### should move this namespace somewhere (with the others!) */
        ap_rputs(" xmlns:m=\"http://apache.org/dav/xmlns\"", r);
    }

    if (err->namespace != NULL) {
        ap_rprintf(r,
                   " xmlns:C=\"%s\">" DEBUG_CR
                   "<C:%s/>" DEBUG_CR,
                   err->namespace, err->tagname);
    }
    else {
        ap_rprintf(r,
                   ">" DEBUG_CR
                   "<D:%s/>" DEBUG_CR, err->tagname);
    }

    /* here's our mod_dav specific tag: */
    if (err->desc != NULL) {
        ap_rprintf(r,
                   "<m:human-readable errcode=\"%d\">" DEBUG_CR
