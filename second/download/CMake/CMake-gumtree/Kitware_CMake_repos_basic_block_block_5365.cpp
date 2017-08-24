{
  case SMB_OPEN:
    result = smb_send_open(conn);
    break;

  case SMB_DOWNLOAD:
    result = smb_send_read(conn);
    break;

  case SMB_UPLOAD:
    result = smb_send_write(conn);
    break;

  case SMB_CLOSE:
    result = smb_send_close(conn);
    break;

  case SMB_TREE_DISCONNECT:
    result = smb_send_tree_disconnect(conn);
    break;

  case SMB_DONE:
    result = req->result;
    *done = true;
    break;

  default:
    break;
  }