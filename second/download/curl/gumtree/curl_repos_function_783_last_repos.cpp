char *fuzz_tlv_to_string(TLV *tlv)
{
  char *tlvstr;

  /* Allocate enough space, plus a null terminator */
  tlvstr = (char *)malloc(tlv->length + 1);

  if(tlvstr != NULL) {
    memcpy(tlvstr, tlv->value, tlv->length);
    tlvstr[tlv->length] = 0;
  }

  return tlvstr;
}