#ifdef WIN32

	if (i == SOCKET_ERROR)

	    errno = WSAGetLastError();

#endif /* WIN32 */

    } while (i == -1 && errno == EINTR);

    if (i == -1) {

	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

		     "proxy connect to %s port %d failed",

		     inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));

    }

    ap_kill_timeout(r);



    return i;

}

-- apache_1.3.1/src/modules/standard/mod_access.c	1998-07-09 01:47:12.000000000 +0800

