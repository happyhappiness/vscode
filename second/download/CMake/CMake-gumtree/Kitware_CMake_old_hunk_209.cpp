    else
      tls_rt_name = "";

    msg_type = *(char*)buf;
    msg_name = ssl_msg_type(ssl_ver, msg_type);

    txt_len = snprintf(ssl_buf, sizeof(ssl_buf), "%s (%s), %s, %s (%d):\n",
