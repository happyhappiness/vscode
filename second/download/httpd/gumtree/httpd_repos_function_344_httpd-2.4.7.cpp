static int dav_handle_err(request_rec *r, dav_error *err,
                          dav_response *response)
{
    /* log the errors */
    dav_log_err(r, err, APLOG_ERR);

    if (response == NULL) {
        dav_error *stackerr = err;

        /* our error messages are safe; tell Apache this */
        apr_table_setn(r->notes, "verbose-error-to", "*");

        /* Didn't get a multistatus response passed in, but we still
           might be able to generate a standard <D:error> response.
           Search the error stack for an errortag. */
        while (stackerr != NULL && stackerr->tagname == NULL)
            stackerr = stackerr->prev;

        if (stackerr != NULL && stackerr->tagname != NULL)
            return dav_error_response_tag(r, stackerr);

        return err->status;
    }

    /* send the multistatus and tell Apache the request/response is DONE. */
    dav_send_multistatus(r, err->status, response, NULL);
    return DONE;
}