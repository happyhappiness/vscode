CURLcode Curl_auth_decode_ntlm_type2_message(struct Curl_easy *data,
                                             const char *type2msg,
                                             struct ntlmdata *ntlm)
{
  static const char type2_marker[] = { 0x02, 0x00, 0x00, 0x00 };

  /* NTLM type-2 message structure:

          Index  Description            Content
            0    NTLMSSP Signature      Null-terminated ASCII "NTLMSSP"
                                        (0x4e544c4d53535000)
            8    NTLM Message Type      long (0x02000000)
           12    Target Name            security buffer
           20    Flags                  long
           24    Challenge              8 bytes
          (32)   Context                8 bytes (two consecutive longs) (*)
          (40)   Target Information     security buffer (*)
          (48)   OS Version Structure   8 bytes (*)
  32 (48) (56)   Start of data block    (*)
                                        (*) -> Optional
  */

  CURLcode result = CURLE_OK;
  unsigned char *type2 = NULL;
  size_t type2_len = 0;

#if defined(NTLM_NEEDS_NSS_INIT)
  /* Make sure the crypto backend is initialized */
  result = Curl_nss_force_init(data);
  if(result)
    return result;
#elif defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void)data;
#endif

  /* Decode the base-64 encoded type-2 message */
  if(strlen(type2msg) && *type2msg != '=') {
    result = Curl_base64_decode(type2msg, &type2, &type2_len);
    if(result)
      return result;
  }

  /* Ensure we have a valid type-2 message */
  if(!type2) {
    infof(data, "NTLM handshake failure (empty type-2 message)\n");
    return CURLE_BAD_CONTENT_ENCODING;
  }

  ntlm->flags = 0;

  if((type2_len < 32) ||
     (memcmp(type2, NTLMSSP_SIGNATURE, 8) != 0) ||
     (memcmp(type2 + 8, type2_marker, sizeof(type2_marker)) != 0)) {
    /* This was not a good enough type-2 message */
    free(type2);
    infof(data, "NTLM handshake failure (bad type-2 message)\n");
    return CURLE_BAD_CONTENT_ENCODING;
  }

  ntlm->flags = Curl_read32_le(&type2[20]);
  memcpy(ntlm->nonce, &type2[24], 8);

  if(ntlm->flags & NTLMFLAG_NEGOTIATE_TARGET_INFO) {
    result = ntlm_decode_type2_target(data, type2, type2_len, ntlm);
    if(result) {
      free(type2);
      infof(data, "NTLM handshake failure (bad type-2 message)\n");
      return result;
    }
  }

  DEBUG_OUT({
    fprintf(stderr, "**** TYPE2 header flags=0x%08.8lx ", ntlm->flags);
    ntlm_print_flags(stderr, ntlm->flags);
    fprintf(stderr, "\n                  nonce=");
    ntlm_print_hex(stderr, (char *)ntlm->nonce, 8);
    fprintf(stderr, "\n****\n");
    fprintf(stderr, "**** Header %s\n ", header);
  });

  free(type2);

  return result;
}