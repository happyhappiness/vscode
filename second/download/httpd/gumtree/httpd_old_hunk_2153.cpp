	else

	    ret = FORBIDDEN;

    }



    if (ret == FORBIDDEN

	&& (ap_satisfies(r) != SATISFY_ANY || !ap_some_auth_required(r))) {

	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

		  "client %pI denied by server configuration: %s",

		  &r->connection->remote_addr, r->filename);

    }



    return ret;

}





-- apache_1.3.1/src/modules/standard/mod_actions.c	1998-06-13 23:23:04.000000000 +0800

