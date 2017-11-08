CURLcode Curl_ntlm_decode_type2_message(struct SessionHandle *data,
                                        const char* header,
                                        struct ntlmdata* ntlm)
{
#ifndef USE_WINDOWS_SSPI
  static const char type2_marker[] = { 0x02, 0x00, 0x00, 0x00 };
#endif

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

  size_t size = 0;
  unsigned char *buffer = NULL;
  CURLcode error;

#if defined(CURL_DISABLE_VERBOSE_STRINGS) || defined(USE_WINDOWS_SSPI)
  (void)data;
#endif

  error = Curl_base64_decode(header, &buffer, &size);
  if(error)
    return error;

  if(!buffer) {
    infof(data, "NTLM handshake failure (unhandled condition)\n");
    return CURLE_REMOTE_ACCESS_DENIED;
  }

#ifdef USE_WINDOWS_SSPI
  ntlm->type_2 = malloc(size + 1);
  if(ntlm->type_2 == NULL) {
    free(buffer);
    return CURLE_OUT_OF_MEMORY;
  }
  ntlm->n_type_2 = curlx_uztoul(size);
  memcpy(ntlm->type_2, buffer, size);
#else
  ntlm->flags = 0;

  if((size < 32) ||
     (memcmp(buffer, NTLMSSP_SIGNATURE, 8) != 0) ||
     (memcmp(buffer + 8, type2_marker, sizeof(type2_marker)) != 0)) {
    /* This was not a good enough type-2 message */
    free(buffer);
    infof(data, "NTLM handshake failure (bad type-2 message)\n");
    return CURLE_REMOTE_ACCESS_DENIED;
  }

  ntlm->flags = readint_le(&buffer[20]);
  memcpy(ntlm->nonce, &buffer[24], 8);

  DEBUG_OUT({
    fprintf(stderr, "**** TYPE2 header flags=0x%08.8lx ", ntlm->flags);
    ntlm_print_flags(stderr, ntlm->flags);
    fprintf(stderr, "\n                  nonce=");
    ntlm_print_hex(stderr, (char *)ntlm->nonce, 8);
    fprintf(stderr, "\n****\n");
    fprintf(stderr, "**** Header %s\n ", header);
  });
#endif
  free(buffer);

  return CURLE_OK;
}