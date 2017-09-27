            return status;
        }
    }

    backend->is_ssl = 0;

    /* Step One: Determine Who To Connect To */
    status = ap_proxy_determine_connection(p, r, conf, worker, backend,
                                           uri, &url, proxyname, proxyport,
                                           server_portstr,
                                           sizeof(server_portstr));
    if (status != OK) {
        goto cleanup;
    }

    /* XXX Setting close to 0 is a great way to end up with
     *     timeouts at this point, since we lack good ways to manage the
     *     back end fastcgi processes.  This should be revisited when we
     *     have a better story on that part of things. */
    backend->close = 1;

    /* Step Two: Make the Connection */
    if (ap_proxy_connect_backend(FCGI_SCHEME, backend, worker, r->server)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01079)
                      "failed to make connection to backend: %s",
                      backend->hostname);
        status = HTTP_SERVICE_UNAVAILABLE;
        goto cleanup;
    }

    /* Step Three: Process the Request */
    status = fcgi_do_request(p, r, backend, origin, dconf, uri, url,
                             server_portstr);

cleanup:
    ap_proxy_release_connection(FCGI_SCHEME, backend, r->server);
    return status;
}

static void register_hooks(apr_pool_t *p)
{
