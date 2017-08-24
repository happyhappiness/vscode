{
  const md5_byte_t* p = data;
  size_t left = nbytes;
  size_t offset = (pms->count[0] >> 3) & 63;
  md5_word_t nbits = (md5_word_t)(nbytes << 3);

  if (nbytes <= 0)
    return;

  /* Update the message length. */
  pms->count[1] += (md5_word_t)(nbytes >> 29);
  pms->count[0] += nbits;
  if (pms->count[0] < nbits)
    pms->count[1]++;

  /* Process an initial partial block. */
  if (offset) {
    size_t copy = (offset + nbytes > 64 ? 64 - offset : nbytes);

    memcpy(pms->buf + offset, p, copy);
    if (offset + copy < 64)
      return;
    p += copy;
    left -= copy;
    md5_process(pms, pms->buf);
  }

  /* Process full blocks. */
  for (; left >= 64; p += 64, left -= 64)
    md5_process(pms, p);

  /* Process a final partial block. */
  if (left)
    memcpy(pms->buf, p, left);
}