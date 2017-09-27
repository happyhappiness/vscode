            }

            m_cont = m->next;
            while (m_cont && (m_cont->cont_level != 0)) {
#if MIME_MAGIC_DEBUG
                rule_counter++;
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                        MODNAME ": line=%d mc=%x mc->next=%x cont=%d desc=%s",
                            m_cont->lineno, m_cont,
                            m_cont->next, m_cont->cont_level,
                            m_cont->desc);
#endif
                /*
