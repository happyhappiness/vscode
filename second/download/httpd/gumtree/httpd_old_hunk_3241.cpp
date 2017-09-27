             * of which would make the parent shutdown all
             * children, then idle-loop until it detected that
             * the network is up again, and restart the children.
             * Ben Hyde noted that temporary ENETDOWN situations
             * occur in mobile IP.
             */
            ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
                         "apr_socket_accept: giving up.");
            return APR_EGENERAL;
#endif /*ENETDOWN*/

        default:
            /* If the socket has been closed in ap_close_listeners()
             * by the restart/stop action, we may get EBADF.
             * Do not print an error in this case.
             */
            if (!lr->active) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, status, ap_server_conf,
                             "apr_socket_accept failed for inactive listener");
                return status;
            }
            ap_log_error(APLOG_MARK, APLOG_ERR, status, ap_server_conf,
                         "apr_socket_accept: (client socket)");
            return APR_EGENERAL;
    }
    return status;
}

