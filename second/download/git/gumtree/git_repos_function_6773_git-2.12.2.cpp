static void
internal_function
re_string_translate_buffer (re_string_t *pstr)
{
  int buf_idx, end_idx;
  end_idx = (pstr->bufs_len > pstr->len) ? pstr->len : pstr->bufs_len;

  for (buf_idx = pstr->valid_len; buf_idx < end_idx; ++buf_idx)
    {
      int ch = pstr->raw_mbs[pstr->raw_mbs_idx + buf_idx];
      pstr->mbs[buf_idx] = pstr->trans[ch];
    }

  pstr->valid_len = buf_idx;
  pstr->valid_raw_len = buf_idx;
}