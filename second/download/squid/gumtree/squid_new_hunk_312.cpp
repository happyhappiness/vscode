#endif
            if (!password) {
                fprintf(stderr, "ERROR: WWW password missing\n");
                exit(1);
            }
            snprintf(buf, BUFSIZ, "%s:%s", user, password);
            snprintf(buf, BUFSIZ, "Authorization: Basic %s\r\n", old_base64_encode(buf));
            strcat(msg, buf);
        }
#if HAVE_GSSAPI
        if (www_neg) {
            if (host) {
                snprintf(buf, BUFSIZ, "Authorization: Negotiate %s\r\n", GSSAPI_token(host));
                strcat(msg, buf);
            } else
                fprintf(stderr, "ERROR: server host missing\n");
        }
        if (proxy_neg) {
            if (hostname) {
                snprintf(buf, BUFSIZ, "Proxy-Authorization: Negotiate %s\r\n", GSSAPI_token(hostname));
                strcat(msg, buf);
            } else
                fprintf(stderr, "ERROR: proxy server host missing\n");
        }
#endif

        /* HTTP/1.0 may need keep-alive explicitly */
        if (strcmp(version, "1.0") == 0 && keep_alive)
            strcat(msg, "Connection: keep-alive\r\n");

        /* HTTP/1.1 may need close explicitly */
