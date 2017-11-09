static void request_state(struct connectdata *conn,
                          enum smb_req_state newstate)
{
  struct smb_request *req = conn->data->req.protop;
#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
  /* For debug purposes */
  static const char * const names[] = {
    "SMB_REQUESTING",
    "SMB_TREE_CONNECT",
    "SMB_OPEN",
    "SMB_DOWNLOAD",
    "SMB_UPLOAD",
    "SMB_CLOSE",
    "SMB_TREE_DISCONNECT",
    "SMB_DONE",
    /* LAST */
  };

  if(req->state != newstate)
    infof(conn->data, "SMB request %p state change from %s to %s\n",
          (void *)req, names[req->state], names[newstate]);
#endif

  req->state = newstate;
}