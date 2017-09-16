                --cp;

        }

        else {

#if defined(EACCES)

            if (errno != EACCES)

#endif

                ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

                            "access to %s failed for %s", r->uri,

                            ap_get_remote_host(r->connection, r->per_dir_config,

                                            REMOTE_NOLOOKUP));

            return HTTP_FORBIDDEN;

        }

#else

#error ENOENT || ENOTDIR not defined; please see the

#error comments at this line in the source for a workaround.

        /*

