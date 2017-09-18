                nDeleted++;
            }
        } while (rc == TABLE_ERROR_NONE); 
        /* (vpKeyThis != vpKey) && (nKeyThis != nKey) */
    }
    ssl_mutex_off(s);
    ssl_log(s, SSL_LOG_TRACE, "Inter-Process Session Cache (SHMHT) Expiry: "
            "old: %d, new: %d, removed: %d",
            nElements, nElements-nDeleted, nDeleted);
    return;
}

void ssl_scache_shmht_status(server_rec *s, apr_pool_t *p, void (*func)(char *, void *), void *arg)
{
    SSLModConfigRec *mc = myModConfig(s);
