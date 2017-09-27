            (*runtime)->s = shm;
            (*runtime)->tmutex = NULL;
            if ((rv = ap_proxy_initialize_worker(*runtime, s, conf->pool)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(00966) "Cannot init worker");
                return rv;
            }
        }
    }
    if (b->s->need_reset) {
        if (b->lbmethod && b->lbmethod->reset)
            b->lbmethod->reset(b, s);
        b->s->need_reset = 0;
    }
    b->wupdated = b->s->wupdated;
    return APR_SUCCESS;
}

void proxy_util_register_hooks(apr_pool_t *p)
{
    APR_REGISTER_OPTIONAL_FN(ap_proxy_retry_worker);
}
