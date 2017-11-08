static CURLcode ntlm_decode_type2_target(struct Curl_easy *data,
                                         unsigned char *buffer,
                                         size_t size,
                                         struct ntlmdata *ntlm)
{
  unsigned short target_info_len = 0;
  unsigned int target_info_offset = 0;

#if defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void) data;
#endif

  if(size >= 48) {
    target_info_len = Curl_read16_le(&buffer[40]);
    target_info_offset = Curl_read32_le(&buffer[44]);
    if(target_info_len > 0) {
      if(((target_info_offset + target_info_len) > size) ||
         (target_info_offset < 48)) {
        infof(data, "NTLM handshake failure (bad type-2 message). "
                    "Target Info Offset Len is set incorrect by the peer\n");
        return CURLE_BAD_CONTENT_ENCODING;
      }

      ntlm->target_info = malloc(target_info_len);
      if(!ntlm->target_info)
        return CURLE_OUT_OF_MEMORY;

      memcpy(ntlm->target_info, &buffer[target_info_offset], target_info_len);
    }
  }

  ntlm->target_info_len = target_info_len;

  return CURLE_OK;
}