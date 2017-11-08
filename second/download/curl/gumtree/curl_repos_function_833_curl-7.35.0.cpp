void Curl_ntlm_sspi_cleanup(struct ntlmdata *ntlm)
{
  Curl_safefree(ntlm->type_2);
  if(ntlm->has_handles) {
    s_pSecFn->DeleteSecurityContext(&ntlm->c_handle);
    s_pSecFn->FreeCredentialsHandle(&ntlm->handle);
    ntlm->has_handles = 0;
  }
  if(ntlm->p_identity) {
    Curl_safefree(ntlm->identity.User);
    Curl_safefree(ntlm->identity.Password);
    Curl_safefree(ntlm->identity.Domain);
    ntlm->p_identity = NULL;
  }
}