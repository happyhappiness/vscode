            return shm;
        }
    }
    return NULL;
}

void proxy_util_register_hooks(apr_pool_t *p)
{
    APR_REGISTER_OPTIONAL_FN(ap_proxy_retry_worker);
}
