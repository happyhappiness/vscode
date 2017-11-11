static int imap_handler(request_rec *r)
{
    /* Optimization: skip the allocation of large local variables on the
     * stack (in imap_handler_internal()) on requests that aren't using
     * imagemaps
     */
    if (r->method_number != M_GET || (strcmp(r->handler,IMAP_MAGIC_TYPE)
				      && strcmp(r->handler, "imap-file"))) {
	return DECLINED;
    }
    else {
        return imap_handler_internal(r);
    }
}