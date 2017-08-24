h(req->state) {
  case SMB_TREE_CONNECT:
    if(h->status) {
      req->result = CURLE_REMOTE_FILE_NOT_FOUND;
      if(h->status == smb_swap32(SMB_ERR_NOACCESS))
        req->result = CURLE_REMOTE_ACCESS_DENIED;
      break;
    }
    req->tid = smb_swap16(h->tid);
    next_state = SMB_OPEN;
    break;

  case SMB_OPEN:
    if(h->status || smbc->got < sizeof(struct smb_nt_create_response)) {
      req->result = CURLE_REMOTE_FILE_NOT_FOUND;
      next_state = SMB_TREE_DISCONNECT;
      break;
    }
    req->fid = smb_swap16(((struct smb_nt_create_response *)msg)->fid);
    conn->data->req.offset = 0;
    if(conn->data->set.upload) {
      conn->data->req.size = conn->data->state.infilesize;
      Curl_pgrsSetUploadSize(conn->data, conn->data->req.size);
      next_state = SMB_UPLOAD;
    }
    else {
      conn->data->req.size =
        smb_swap64(((struct smb_nt_create_response *)msg)->end_of_file);
      Curl_pgrsSetDownloadSize(conn->data, conn->data->req.size);
      next_state = SMB_DOWNLOAD;
    }
    break;

  case SMB_DOWNLOAD:
    if(h->status || smbc->got < sizeof(struct smb_header) + 14) {
      req->result = CURLE_RECV_ERROR;
      next_state = SMB_CLOSE;
      break;
    }
    len = Curl_read16_le(((const unsigned char *) msg) +
                         sizeof(struct smb_header) + 11);
    off = Curl_read16_le(((const unsigned char *) msg) +
                         sizeof(struct smb_header) + 13);
    if(len > 0) {
      if(off + sizeof(unsigned int) + len > smbc->got) {
        failf(conn->data, "Invalid input packet");
        result = CURLE_RECV_ERROR;
      }
      else
        result = Curl_client_write(conn, CLIENTWRITE_BODY,
                                   (char *)msg + off + sizeof(unsigned int),
                                   len);
      if(result) {
        req->result = result;
        next_state = SMB_CLOSE;
        break;
      }
    }
    conn->data->req.bytecount += len;
    conn->data->req.offset += len;
    Curl_pgrsSetDownloadCounter(conn->data, conn->data->req.bytecount);
    next_state = (len < MAX_PAYLOAD_SIZE) ? SMB_CLOSE : SMB_DOWNLOAD;
    break;

  case SMB_UPLOAD:
    if(h->status || smbc->got < sizeof(struct smb_header) + 6) {
      req->result = CURLE_UPLOAD_FAILED;
      next_state = SMB_CLOSE;
      break;
    }
    len = Curl_read16_le(((const unsigned char *) msg) +
                         sizeof(struct smb_header) + 5);
    conn->data->req.bytecount += len;
    conn->data->req.offset += len;
    Curl_pgrsSetUploadCounter(conn->data, conn->data->req.bytecount);
    if(conn->data->req.bytecount >= conn->data->req.size)
      next_state = SMB_CLOSE;
    else
      next_state = SMB_UPLOAD;
    break;

  case SMB_CLOSE:
    /* We don't care if the close failed, proceed to tree disconnect anyway */
    next_state = SMB_TREE_DISCONNECT;
    break;

  case SMB_TREE_DISCONNECT:
    next_state = SMB_DONE;
    break;

  default:
    smb_pop_message(conn);
    return CURLE_OK; /* ignore */
  }