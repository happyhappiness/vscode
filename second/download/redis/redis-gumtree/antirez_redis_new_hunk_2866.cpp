                if (slaves) flushSlavesOutputBuffers();
            }
        }
        if (!keys_freed) return REDIS_ERR; /* nothing to free... */
    }
    return REDIS_OK;
}

