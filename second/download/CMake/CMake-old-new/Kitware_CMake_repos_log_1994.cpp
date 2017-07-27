txt_len = snprintf(ssl_buf, sizeof(ssl_buf), "%s (%s), %s, %s (%d):\n",
                       verstr, direction?"OUT":"IN",
                       tls_rt_name, msg_name, msg_type);