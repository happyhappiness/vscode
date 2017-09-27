        return AJP_EBAD_HEADER;
    }
    rc = ajp_msg_get_uint16(msg, len);
    if (rc != APR_SUCCESS) {
        return rc;
    }
    *ptr = (char *)&(msg->buf[msg->pos]);
    return APR_SUCCESS;
}

/*
 * Allocate a msg to send data
