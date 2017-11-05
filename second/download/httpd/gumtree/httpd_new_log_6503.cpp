ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02403)
                         "grabbing shm[%d] (0x%pp) for worker: %s", i, (void *)shm,
                         (*runtime)->s->name);