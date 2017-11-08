void dav_add_vary_header(request_rec *in_req,
			 request_rec *out_req,
			 const dav_resource *resource)
{
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(in_req);

    /* ### this is probably all wrong... I think there is a function in
       ### the Apache API to add things to the Vary header. need to check */

    /* Only versioning headers require a Vary response header,
     * so only do this check if there is a versioning provider */
    if (vsn_hooks != NULL) {
	const char *target = apr_table_get(in_req->headers_in, DAV_LABEL_HDR);
	const char *vary = apr_table_get(out_req->headers_out, "Vary");

        /* If Target-Selector specified, add it to the Vary header */
	if (target != NULL) {
	    if (vary == NULL)
		vary = DAV_LABEL_HDR;
	    else
		vary = apr_pstrcat(out_req->pool, vary, "," DAV_LABEL_HDR,
                                   NULL);

	    apr_table_setn(out_req->headers_out, "Vary", vary);
	}
    }
}