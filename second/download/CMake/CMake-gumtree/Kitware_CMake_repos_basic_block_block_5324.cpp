{
  struct smb_request *req;

  /* Initialize the request state */
  conn->data->req.protop = req = calloc(1, sizeof(struct smb_request));
  if(!req)
    return CURLE_OUT_OF_MEMORY;

  /* Parse the URL path */
  return smb_parse_url_path(conn);
}