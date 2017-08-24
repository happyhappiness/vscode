f(r->m_read.status == RTMP_READ_COMPLETE ||
        r->m_read.status == RTMP_READ_EOF) {
      conn->data->req.size = conn->data->req.bytecount;
      nread = 0;
    }
    else
      *err = CURLE_RECV_ERROR