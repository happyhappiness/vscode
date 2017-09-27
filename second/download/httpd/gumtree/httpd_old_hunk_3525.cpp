        }
        return next->frec->filter_func.out_func(next, bb);
    }
    return AP_NOBODY_WROTE;
}

AP_DECLARE(apr_status_t) ap_save_brigade(ap_filter_t *f,
                                         apr_bucket_brigade **saveto,
                                         apr_bucket_brigade **b, apr_pool_t *p)
{
    apr_bucket *e;
    apr_status_t rv, srv = APR_SUCCESS;
