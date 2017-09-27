            break;
        case USE_CANONICAL_NAME_OFF:
        case USE_CANONICAL_NAME_UNSET:
            retval = r->hostname ? r->hostname : r->server->server_hostname;
            break;
        default:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                         "ap_get_server_name: Invalid UCN Option somehow");
            retval = "localhost";
            break;
    }
    return retval;
}
