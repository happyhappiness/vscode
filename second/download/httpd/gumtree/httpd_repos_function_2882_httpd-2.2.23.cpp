static const char *dbd_oracle_error(apr_dbd_t *sql, int n)
{
    /* This is ugly.  Needs us to pass in a buffer of unknown size.
     * Either we put it on the handle, or we have to keep allocing/copying
     */
    sb4 errorcode;

    switch (sql->status) {
    case OCI_SUCCESS:
        return "OCI_SUCCESS";
    case OCI_SUCCESS_WITH_INFO:
        return "OCI_SUCCESS_WITH_INFO";
    case OCI_NEED_DATA:
        return "OCI_NEED_DATA";
    case OCI_NO_DATA:
        return "OCI_NO_DATA";
    case OCI_INVALID_HANDLE:
        return "OCI_INVALID_HANDLE";
    case OCI_STILL_EXECUTING:
        return "OCI_STILL_EXECUTING";
    case OCI_CONTINUE:
        return "OCI_CONTINUE";
    }

    switch (OCIErrorGet(sql->err, 1, NULL, &errorcode,
                        (text*) sql->buf, sizeof(sql->buf), OCI_HTYPE_ERROR)) {
    case OCI_SUCCESS:
        return sql->buf; 
    default:
        return "internal error: OCIErrorGet failed";
    }
}