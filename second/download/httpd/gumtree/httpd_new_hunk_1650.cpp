    apr_size_t msglen;

    if (!((head[0] == 0x41 && head[1] == 0x42) ||
          (head[0] == 0x12 && head[1] == 0x34))) {

        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                      "ajp_check_msg_header() got bad signature %02x%02x",
                      head[0], head[1]);

        return AJP_EBAD_SIGNATURE;
    }

    msglen  = ((head[2] & 0xff) << 8);
