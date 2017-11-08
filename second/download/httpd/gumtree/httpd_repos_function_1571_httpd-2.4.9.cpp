static void set_vlist_validator(request_rec *r, request_rec *vlistr)
{
    /* Calculating the variant list validator is similar to
     * calculating an etag for the source of the variant list
     * information, so we use ap_make_etag().  Note that this
     * validator can be 'weak' in extreme case.
     */
    ap_update_mtime(vlistr, vlistr->finfo.mtime);
    r->vlist_validator = ap_make_etag(vlistr, 0);

    /* ap_set_etag will later take r->vlist_validator into account
     * when creating the etag header
     */
}