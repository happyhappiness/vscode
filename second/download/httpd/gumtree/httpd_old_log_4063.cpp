ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                MODNAME ": match conf=%x file=%s m=%s m->next=%s last=%s",
                conf,
                conf->magicfile ? conf->magicfile : "NULL",
                conf->magic ? "set" : "NULL",
                (conf->magic && conf->magic->next) ? "set" : "NULL",
                conf->last ? "set" : "NULL");