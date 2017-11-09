int fuzz_get_next_tlv(FUZZ_DATA *fuzz,
                      TLV *tlv)
{
  /* Advance the cursor by the full length of the previous TLV. */
  fuzz->state.data_pos += sizeof(TLV_RAW) + tlv->length;

  /* Work out if there's a TLV's worth of data to read */
  if(fuzz->state.data_pos + sizeof(TLV_RAW) > fuzz->state.data_len) {
    /* No more TLVs to parse */
    return TLV_RC_NO_MORE_TLVS;
  }

  return fuzz_get_tlv_comn(fuzz, tlv);
}