            APR_BRIGADE_INSERT_TAIL(to, new);
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00964)
                          "Unhandled bucket type of type %s in"
                          " proxy_buckets_lifetime_transform", e->type->name);
            apr_bucket_delete(e);
            rv = APR_EGENERAL;
        }
    }
    return rv;
}

