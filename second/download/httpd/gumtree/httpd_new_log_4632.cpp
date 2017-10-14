ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02293)
                     "slotmem(%s) grab failed. Num %u/num_free %u",
                     slot->name, slotmem_num_slots(slot),
                     slotmem_num_free_slots(slot));