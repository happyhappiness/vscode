static apr_status_t freeStatement(void *statement)
{
    int rv = APR_SUCCESS;
    OCIStmt *stmt = ((apr_dbd_prepared_t*)statement)->stmt;

#ifdef PREPARE2
    OCIError *err;

    if (OCIHandleAlloc(dbd_oracle_env, (dvoid**)&err, OCI_HTYPE_ERROR,
                       0, NULL) != OCI_SUCCESS) {
        return APR_EGENERAL;
    }
    if (OCIStmtRelease(stmt, err, NULL, 0, OCI_DEFAULT) != OCI_SUCCESS) {
        rv = APR_EGENERAL;
    }
    if (OCIHandleFree(err, OCI_HTYPE_ERROR) != OCI_SUCCESS) {
        rv = APR_EGENERAL;
    }
#else
    if (OCIHandleFree(stmt, OCI_HTYPE_STMT) != OCI_SUCCESS) {
        rv = APR_EGENERAL;
    }
#endif

    return rv;
}