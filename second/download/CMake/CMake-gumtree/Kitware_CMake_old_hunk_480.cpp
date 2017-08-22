    fprintf(stderr, "\n****\n");
    fprintf(stderr, "**** Header %s\n ", header);
  });
#endif
  free(buffer);

  return CURLE_OK;
}

#ifdef USE_WINDOWS_SSPI
void Curl_ntlm_sspi_cleanup(struct ntlmdata *ntlm)
{
  Curl_safefree(ntlm->type_2);

  if(ntlm->has_handles) {
    s_pSecFn->DeleteSecurityContext(&ntlm->c_handle);
    s_pSecFn->FreeCredentialsHandle(&ntlm->handle);
    ntlm->has_handles = 0;
  }

  ntlm->max_token_length = 0;
  Curl_safefree(ntlm->output_token);

  Curl_sspi_free_identity(ntlm->p_identity);
  ntlm->p_identity = NULL;
}
#endif

#ifndef USE_WINDOWS_SSPI
/* copy the source to the destination and fill in zeroes in every
   other destination byte! */
static void unicodecpy(unsigned char *dest, const char *src, size_t length)
