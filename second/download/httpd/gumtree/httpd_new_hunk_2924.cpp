
        /* For intranet (Internal proxies) ignore all restrictions below */
        if (!internal
              && ((temp_sa->family == APR_INET
                   /* For internet (non-Internal proxies) deny all
                    * RFC3330 designated local/private subnets:
                    * 10.0.0.0/8   169.254.0.0/16  192.168.0.0/16
                    * 127.0.0.0/8  172.16.0.0/12
                    */
                      && (addrbyte[0] == 10
                       || addrbyte[0] == 127
                       || (addrbyte[0] == 169 && addrbyte[1] == 254)
                       || (addrbyte[0] == 172 && (addrbyte[1] & 0xf0) == 16)
                       || (addrbyte[0] == 192 && addrbyte[1] == 168)))
#if APR_HAVE_IPV6
               || (temp_sa->family == APR_INET6
                   /* For internet (non-Internal proxies) we translated
                    * IPv4-over-IPv6-mapped addresses as IPv4, above.
                    * Accept only Global Unicast 2000::/3 defined by RFC4291
                    */
                      && ((temp_sa->sa.sin6.sin6_addr.s6_addr[0] & 0xe0) != 0x20))
#endif
        )) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG,  rv, r, APLOGNO(01569)
                          "RemoteIP: Header %s value of %s appears to be "
                          "a private IP or nonsensical.  Ignored",
                          config->header_name, parse_remote);
            if (remote) {
                *(remote + strlen(remote)) = ',';
            }
            else {
                remote = parse_remote;
            }

            break;
        }

        /* save away our results */
        if (!req) {
            req = (remoteip_req_t *) apr_palloc(r->pool, sizeof(remoteip_req_t));
        }

        /* Set useragent_ip string */
        if (!internal) {
            if (proxy_ips) {
                proxy_ips = apr_pstrcat(r->pool, proxy_ips, ", ",
                                        c->client_ip, NULL);
            }
            else {
                proxy_ips = c->client_ip;
            }
        }

        req->useragent_addr = temp_sa;
        apr_sockaddr_ip_get(&req->useragent_ip, req->useragent_addr);
    }

    /* Nothing happened? */
    if (!req) {
        return OK;
    }

    req->proxied_remote = remote;
    req->proxy_ips = proxy_ips;

    if (req->proxied_remote) {
        apr_table_setn(r->headers_in, config->header_name,
                       req->proxied_remote);
    }
    else {
        apr_table_unset(r->headers_in, config->header_name);
    }
    if (req->proxy_ips) {
        apr_table_setn(r->notes, "remoteip-proxy-ip-list", req->proxy_ips);
        if (config->proxies_header_name) {
            apr_table_setn(r->headers_in, config->proxies_header_name,
                           req->proxy_ips);
        }
    }

    r->useragent_addr = req->useragent_addr;
    r->useragent_ip = req->useragent_ip;

    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                  req->proxy_ips
                      ? "Using %s as client's IP by proxies %s"
                      : "Using %s as client's IP by internal proxies",
                  req->useragent_ip, req->proxy_ips);
    return OK;
}

static const command_rec remoteip_cmds[] =
{
    AP_INIT_TAKE1("RemoteIPHeader", header_name_set, NULL, RSRC_CONF,
