CURLntlm Curl_input_ntlm(struct connectdata *conn,
                         bool proxy,   /* if proxy or not */
                         char *header) /* rest of the www-authenticate:
                                          header */
{
  /* point to the correct struct with this */
  struct ntlmdata *ntlm;

  ntlm = proxy?&conn->proxyntlm:&conn->ntlm;

  /* skip initial whitespaces */
  while(*header && isspace((int)*header))
    header++;

  if(checkprefix("NTLM", header)) {
    header += strlen("NTLM");

    while(*header && isspace((int)*header))
      header++;

    if(*header) {
      /* We got a type-2 message here:

         Index   Description         Content
         0       NTLMSSP Signature   Null-terminated ASCII "NTLMSSP"
                                     (0x4e544c4d53535000)
         8       NTLM Message Type   long (0x02000000)
         12      Target Name         security buffer(*)
         20      Flags               long
         24      Challenge           8 bytes
         (32)    Context (optional)  8 bytes (two consecutive longs)
         (40)    Target Information  (optional) security buffer(*)
         32 (48) start of data block
      */
      size_t size;
      unsigned char *buffer;
      size = Curl_base64_decode(header, &buffer);
      if(!buffer)
        return CURLNTLM_BAD;

      ntlm->state = NTLMSTATE_TYPE2; /* we got a type-2 */

#ifdef USE_WINDOWS_SSPI
      if ((ntlm->type_2 = malloc(size+1)) == NULL) {
        free(buffer);
        return CURLE_OUT_OF_MEMORY;
      }
      ntlm->n_type_2 = size;
      memcpy(ntlm->type_2, buffer, size);
#else
      if(size >= 48)
        /* the nonce of interest is index [24 .. 31], 8 bytes */
        memcpy(ntlm->nonce, &buffer[24], 8);
      /* FIX: add an else here! */

      /* at index decimal 20, there's a 32bit NTLM flag field */

      free(buffer);
#endif
    }
    else {
      if(ntlm->state >= NTLMSTATE_TYPE1)
        return CURLNTLM_BAD;

      ntlm->state = NTLMSTATE_TYPE1; /* we should sent away a type-1 */
    }
  }
  return CURLNTLM_FINE;
}