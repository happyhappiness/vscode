ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r,
			MODNAME ": line=%d mc=%x mc->next=%x cont=%d desc=%s",
			    m_cont->lineno, m_cont,
			    m_cont->next, m_cont->cont_level,
			    m_cont->desc);