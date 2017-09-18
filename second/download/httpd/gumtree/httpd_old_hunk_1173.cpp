        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                     "Error: %d with ioctl (SO_TLS_SET_CLIENT)", WSAGetLastError());
	}		
	return rcode;
}

static const char *set_secure_listener(cmd_parms *cmd, void *dummy, 
                                       const char *ips, const char* key, 
                                       const char* mutual)
{
    NWSSLSrvConfigRec* sc = get_nwssl_cfg(cmd->server);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
