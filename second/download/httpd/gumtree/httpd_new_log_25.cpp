ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, r->server,
			 "proxy GC: Cache is %ld%% full (nothing deleted)",
			 (long)(((curbytes.upper<<20)|(curbytes.lower>>10))*100/conf->space));