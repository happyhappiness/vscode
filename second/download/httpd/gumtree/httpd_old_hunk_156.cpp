        return *methnum;
        
    if (cur_method_number > METHOD_NUMBER_LAST) {
        /* The method registry  has run out of dynamically
         * assignable method numbers. Log this and return M_INVALID.
         */
        ap_log_perror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, p,
                      "Maximum new request methods %d reached while "
                      "registering method %s.",
                      METHOD_NUMBER_LAST, methname);
        return M_INVALID;
    }

