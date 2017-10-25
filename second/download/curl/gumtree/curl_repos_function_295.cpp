static void
ntlm_sspi_cleanup(struct ntlmdata *ntlm)
{
  if (ntlm->type_2) {
    free(ntlm->type_2);
    ntlm->type_2 = NULL;
  }
  if (ntlm->has_handles) {
    DeleteSecurityContext(&ntlm->c_handle);
    FreeCredentialsHandle(&ntlm->handle);
    ntlm->has_handles = 0;
  }
  if (ntlm->p_identity) {
    if (ntlm->identity.User) free(ntlm->identity.User);
    if (ntlm->identity.Password) free(ntlm->identity.Password);
    if (ntlm->identity.Domain) free(ntlm->identity.Domain);
    ntlm->p_identity = NULL;
  }
}