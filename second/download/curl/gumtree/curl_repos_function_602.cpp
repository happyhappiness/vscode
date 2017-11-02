static void init_httprequest(struct httprequest *req)
{
  /* Pipelining is already set, so do not initialize it here. Only initialize
     checkindex and offset if pipelining is not set, since in a pipeline they
     need to be inherited from the previous request. */
  if(!req->pipelining) {
    req->checkindex = 0;
    req->offset = 0;
  }
  req->testno = DOCNUMBER_NOTHING;
  req->partno = 0;
  req->connect_request = FALSE;
  req->open = TRUE;
  req->auth_req = FALSE;
  req->auth = FALSE;
  req->cl = 0;
  req->digest = FALSE;
  req->ntlm = FALSE;
  req->pipe = 0;
  req->skip = 0;
  req->writedelay = 0;
  req->rcmd = RCMD_NORMALREQ;
  req->prot_version = 0;
  req->callcount = 0;
  req->connect_port = 0;
  req->done_processing = 0;
}