        ap_method_registry_init(p);
    }

    if (methname == NULL) {
        return M_INVALID;
    }

    /* Check if the method was previously registered.  If it was
     * return the associated method number.
     */
    methnum = (int *)apr_hash_get(methods_registry, methname,
                                  APR_HASH_KEY_STRING);
    if (methnum != NULL)
        return *methnum;

    if (cur_method_number > METHOD_NUMBER_LAST) {
        /* The method registry  has run out of dynamically
         * assignable method numbers. Log this and return M_INVALID.
         */
        ap_log_perror(APLOG_MARK, APLOG_ERR, 0, p,
                      "Maximum new request methods %d reached while "
