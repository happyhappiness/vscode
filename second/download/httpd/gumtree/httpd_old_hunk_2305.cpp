
                shmcb_cyclic_cton_memcpy(header->subcache_data_size, dest,
                                         SHMCB_DATA(header, subcache),
                                         data_offset, dest_len);
                dest[dest_len] = '\0';

                rv = (*iterator)(instance, s, id, idx->id_len,
                                 dest, dest_len, pool);
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                             "shmcb_subcache_iterate discarding expired entry");
                if (rv != APR_SUCCESS)
                    return rv;
            }
            else {
                /* Already stale, quietly remove and treat as not-found */
                idx->removed = 1;
