static void
chrony_init_req(tChrony_Request * p_req)
{
  memset(p_req, 0, sizeof(*p_req));
  p_req->header.f_version = PROTO_VERSION_NUMBER;
  p_req->header.f_type    = PKT_TYPE_CMD_REQUEST;
  p_req->header.f_dummy0  = 0;
  p_req->header.f_dummy1  = 0;
  p_req->header.f_dummy2  = 0;
  p_req->header.f_dummy3  = 0;
}