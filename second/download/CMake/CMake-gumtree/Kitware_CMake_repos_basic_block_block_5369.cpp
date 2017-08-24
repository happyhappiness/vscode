{
      req->result = CURLE_RECV_ERROR;
      next_state = SMB_CLOSE;
      break;
    }