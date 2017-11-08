void Curl_schannel_session_free(void *ptr)
{
  struct curl_schannel_cred *cred = ptr;

  if(cred && cred->cached && cred->refcount == 0) {
    s_pSecFn->FreeCredentialsHandle(&cred->cred_handle);
    Curl_safefree(cred);
  }
}