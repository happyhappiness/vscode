                if (slaves) flushSlavesOutputBuffers();
            }
        }
        if (!keys_freed) {
            if (debug) printf("-freed: %zu\n\n", mem_freed);
            return REDIS_ERR; /* nothing to free... */
        }
    }
    if (debug) printf("+freed: %zu\n\n", mem_freed);
    return REDIS_OK;
}

