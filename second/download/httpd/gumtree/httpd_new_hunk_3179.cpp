
            auth_line = ap_pbase64decode(r->pool, auth_line);
            username = ap_getword_nulls(r->pool, &auth_line, ':');
            password = auth_line;

            if ((username[0] == '/') && strEQ(password, "password")) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02035)
                    "Encountered FakeBasicAuth spoof: %s", username);
                return HTTP_FORBIDDEN;
            }
        }
    }

