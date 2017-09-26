        }
        /* This should not fail, but if it does, we are in BIG trouble
         * cause we just stomped all over the heap.
         */
        AP_DEBUG_ASSERT(obj->count <= mobj->m_len);
    }
    return APR_SUCCESS;
}
/**
 * Configuration and start-up
 */
static int mem_cache_post_config(apr_pool_t *p, apr_pool_t *plog,
