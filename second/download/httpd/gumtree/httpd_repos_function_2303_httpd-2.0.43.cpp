static apr_status_t db2s(int dberr)
{
    if (dberr != 0) {
        /* ### need to fix this */
        return APR_OS_START_USEERR + dberr;
    }

    return APR_SUCCESS;
}