        for (i = 0; i < arr->nelts; ++i) {
            ap_rvputs(r, elts[i].key, "=", elts[i].val, "\n", NULL);
        }
        return 0;
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                    "printenv directive does not take tags in %s",
		    r->filename);
        ap_rputs(error, r);
        return -1;
    }
}
