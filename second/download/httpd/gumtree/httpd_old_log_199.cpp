ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		  "client %pI denied by server configuration: %s",
		  &r->connection->remote_addr, r->filename);