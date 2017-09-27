             */
            ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
                         "apr_socket_accept: giving up.");
            return APR_EGENERAL;
#endif /*ENETDOWN*/

#ifdef TPF
        case EINACT:
            ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
                         "offload device inactive");
            return APR_EGENERAL;
            break;
        default:
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf,
                         "select/accept error (%d)", status);
            return APR_EGENERAL;
#else
        default:
            ap_log_error(APLOG_MARK, APLOG_ERR, status, ap_server_conf,
                         "apr_socket_accept: (client socket)");
            return APR_EGENERAL;
#endif
    }
    return status;
}


#ifdef _OSD_POSIX
