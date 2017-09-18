		break;
        }
        else
            break;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
		 "proxy: CONNECT: finished with poll() - cleaning up");

    /*
     * Step Five: Clean Up
     *
     * Close the socket and clean up
