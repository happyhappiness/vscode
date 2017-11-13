ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01532)
                        MODNAME ": line=%d mc=%x mc->next=%x cont=%d desc=%s",
                            m_cont->lineno, m_cont,
                            m_cont->next, m_cont->cont_level,
                            m_cont->desc);