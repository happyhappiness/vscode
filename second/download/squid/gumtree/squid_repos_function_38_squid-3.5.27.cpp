static void
reset_auth(cachemgr_request * req)
{
    safe_free(req->passwd);
    safe_free(req->pub_auth);
}