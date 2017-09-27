     * done.
     */
    if (rows != 0) {
        return APR_SUCCESS;
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01860)
                  "the session insert query did not cause any rows to be added "
                  "to the database for session '%s', session not inserted", key);

    return APR_EGENERAL;

}
