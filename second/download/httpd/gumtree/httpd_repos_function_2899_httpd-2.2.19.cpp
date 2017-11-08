static apr_status_t dbd_oracle_close(apr_dbd_t *handle)
{
    /* FIXME: none of the oracle docs/examples say anything about
     * closing/releasing handles.  Which seems unlikely ...
     */

    /* OK, let's grab from cdemo again.
     * cdemo81 does nothing; cdemo82 does OCIHandleFree on the handles
     */
    switch (OCISessionEnd(handle->svc, handle->err, handle->auth,
            (ub4)OCI_DEFAULT)) {
    default:
        break;
    }
    switch (OCIServerDetach(handle->svr, handle->err, (ub4) OCI_DEFAULT )) {
    default:
        break;
    }
    /* does OCISessionEnd imply this? */
    switch (OCIHandleFree((dvoid *) handle->auth, (ub4) OCI_HTYPE_SESSION)) {
    default:
        break;
    }
    switch (OCIHandleFree((dvoid *) handle->svr, (ub4) OCI_HTYPE_SERVER)) {
    default:
        break;
    }
    switch (OCIHandleFree((dvoid *) handle->svc, (ub4) OCI_HTYPE_SVCCTX)) {
    default:
        break;
    }
    switch (OCIHandleFree((dvoid *) handle->err, (ub4) OCI_HTYPE_ERROR)) {
    default:
        break;
    }
    return APR_SUCCESS;
}