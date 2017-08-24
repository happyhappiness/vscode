{
  case SMB_NEGOTIATE:
    if(h->status || smbc->got < sizeof(*nrsp) + sizeof(smbc->challenge) - 1) {
      connclose(conn, "SMB: negotiation failed");
      return CURLE_COULDNT_CONNECT;
    }
    nrsp = msg;
    memcpy(smbc->challenge, nrsp->bytes, sizeof(smbc->challenge));
    smbc->session_key = smb_swap32(nrsp->session_key);
    result = smb_send_setup(conn);
    if(result) {
      connclose(conn, "SMB: failed to send setup message");
      return result;
    }
    conn_state(conn, SMB_SETUP);
    break;

  case SMB_SETUP:
    if(h->status) {
      connclose(conn, "SMB: authentication failed");
      return CURLE_LOGIN_DENIED;
    }
    smbc->uid = smb_swap16(h->uid);
    conn_state(conn, SMB_CONNECTED);
    *done = true;
    break;

  default:
    smb_pop_message(conn);
    return CURLE_OK; /* ignore */
  }