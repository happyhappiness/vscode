f(pp->cache)
          memcpy(pp->cache, pp->linestart_resp, pp->cache_size);
        else
          return CURLE_OUT_OF_MEMORY;