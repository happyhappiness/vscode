static void Curl_schannel_session_free(void *ptr)
{
  /* this is expected to be called under sessionid lock */
  struct curl_schannel_cred *cred = ptr;

  cred->refcount--;
  if(cred->refcount == 0) {
    s_pSecFn->FreeCredentialsHandle(&cred->cred_handle);
    Curl_safefree(cred);
  }
}