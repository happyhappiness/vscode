static apr_status_t ndbm2s(int ndbmerr)
{
    if (ndbmerr == -1) {
        /* ### need to fix this */
        return APR_EGENERAL;
    }

    return APR_SUCCESS;
}