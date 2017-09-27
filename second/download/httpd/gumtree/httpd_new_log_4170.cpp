r(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01533)
                    MODNAME ": rule matched, line=%d type=%d %s",
                    m->lineno, m->type,
                    (m->type == STRING) ? m->value.s : "");