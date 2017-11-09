int fuzz_parse_tlv(FUZZ_DATA *fuzz, TLV *tlv)
{
  int rc;
  char *tmp;

  switch(tlv->type) {
    case TLV_TYPE_RESPONSE1:
      /* The pointers in the TLV will always be valid as long as the fuzz data
         is in scope, which is the entirety of this file. */
      fuzz->rsp1_data = tlv->value;
      fuzz->rsp1_data_len = tlv->length;
      break;

    case TLV_TYPE_UPLOAD1:
      /* The pointers in the TLV will always be valid as long as the fuzz data
         is in scope, which is the entirety of this file. */
      fuzz->upload1_data = tlv->value;
      fuzz->upload1_data_len = tlv->length;

      curl_easy_setopt(fuzz->easy, CURLOPT_UPLOAD, 1L);
      curl_easy_setopt(fuzz->easy,
                       CURLOPT_INFILESIZE_LARGE,
                       (curl_off_t)fuzz->upload1_data_len);
      break;

    case TLV_TYPE_HEADER:
      tmp = fuzz_tlv_to_string(tlv);
      fuzz->header_list = curl_slist_append(fuzz->header_list, tmp);
      fuzz_free((void **)&tmp);
      break;

    case TLV_TYPE_MAIL_RECIPIENT:
      tmp = fuzz_tlv_to_string(tlv);
      fuzz->mail_recipients_list =
                             curl_slist_append(fuzz->mail_recipients_list, tmp);
      fuzz_free((void **)&tmp);
      break;

    /* Define a set of singleton TLVs - they can only have their value set once
       and all follow the same pattern. */
    FSINGLETONTLV(TLV_TYPE_URL, url, CURLOPT_URL);
    FSINGLETONTLV(TLV_TYPE_USERNAME, username, CURLOPT_USERNAME);
    FSINGLETONTLV(TLV_TYPE_PASSWORD, password, CURLOPT_PASSWORD);
    FSINGLETONTLV(TLV_TYPE_POSTFIELDS, postfields, CURLOPT_POSTFIELDS);
    FSINGLETONTLV(TLV_TYPE_COOKIE, cookie, CURLOPT_COOKIE);
    FSINGLETONTLV(TLV_TYPE_RANGE, range, CURLOPT_RANGE);
    FSINGLETONTLV(TLV_TYPE_CUSTOMREQUEST, customrequest, CURLOPT_CUSTOMREQUEST);
    FSINGLETONTLV(TLV_TYPE_MAIL_FROM, mail_from, CURLOPT_MAIL_FROM);

    default:
      /* The fuzzer generates lots of unknown TLVs - we don't want these in the
         corpus so we reject any unknown TLVs. */
      rc = 255;
      goto EXIT_LABEL;
      break;
  }

  rc = 0;

EXIT_LABEL:

  return rc;
}