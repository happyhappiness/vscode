{
      req->result = CURLE_REMOTE_FILE_NOT_FOUND;
      next_state = SMB_TREE_DISCONNECT;
      break;
    }