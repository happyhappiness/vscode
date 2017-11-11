int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  int rc = 0;
  int tlv_rc;
  FUZZ_DATA fuzz;
  TLV tlv;

  /* Have to set all fields to zero before getting to the terminate function */
  memset(&fuzz, 0, sizeof(FUZZ_DATA));

  if(size < sizeof(TLV_RAW)) {
    /* Not enough data for a single TLV - don't continue */
    goto EXIT_LABEL;
  }

  /* Try to initialize the fuzz data */
  FTRY(fuzz_initialize_fuzz_data(&fuzz, data, size));

  for(tlv_rc = fuzz_get_first_tlv(&fuzz, &tlv);
      tlv_rc == 0;
      tlv_rc = fuzz_get_next_tlv(&fuzz, &tlv)) {

    /* Have the TLV in hand. Parse the TLV. */
    rc = fuzz_parse_tlv(&fuzz, &tlv);

    if(rc != 0) {
      /* Failed to parse the TLV. Can't continue. */
      goto EXIT_LABEL;
    }
  }

  if(tlv_rc != TLV_RC_NO_MORE_TLVS) {
    /* A TLV call failed. Can't continue. */
    goto EXIT_LABEL;
  }

  /* Do the CURL stuff! */
  if(fuzz.header_list != NULL) {
    curl_easy_setopt(fuzz.easy, CURLOPT_HTTPHEADER, fuzz.header_list);
  }

  if(fuzz.mail_recipients_list != NULL) {
    curl_easy_setopt(fuzz.easy, CURLOPT_MAIL_RCPT, fuzz.mail_recipients_list);
  }

  curl_easy_perform(fuzz.easy);

EXIT_LABEL:

  fuzz_terminate_fuzz_data(&fuzz);

  /* This function must always return 0. Non-zero codes are reserved. */
  return 0;
}