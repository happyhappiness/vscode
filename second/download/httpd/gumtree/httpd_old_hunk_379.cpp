                               shmcb_get_safe_uint(cache->pos_count) -
                               shmcb_cyclic_space(header->cache_data_size,
                                                  shmcb_get_safe_uint(cache->first_pos),
                                                  shmcb_get_safe_uint(&(idx->offset))));
            shmcb_set_safe_uint(cache->first_pos, shmcb_get_safe_uint(&(idx->offset)));
        }
        ssl_log(s, SSL_LOG_TRACE, "we now have %u sessions",
                shmcb_get_safe_uint(queue->pos_count));
    }
    header->num_expiries += loop;
    return loop;
}

/* Inserts a new encoded session into a queue/cache pair - expiring
