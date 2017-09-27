    rp->request_config  = ap_create_request_config(c->pool);
    proxy_run_create_req(r, rp);

    return rp;
}


/*
 * list is a comma-separated list of case-insensitive tokens, with
 * optional whitespace around the tokens.
 * The return returns 1 if the token val is found in the list, or 0
 * otherwise.
