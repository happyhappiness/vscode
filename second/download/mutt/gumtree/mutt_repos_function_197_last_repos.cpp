char *mutt_concatn_path (char *dst, size_t dstlen,
    const char *dir, size_t dirlen, const char *fname, size_t fnamelen)
{
  size_t req;
  size_t offset = 0;

  if (dstlen == 0)
    return NULL; /* probably should not mask errors like this */

  /* size check */
  req = dirlen + fnamelen + 1; /* +1 for the trailing nul */
  if (dirlen && fnamelen)
    req++; /* when both components are non-nul, we add a "/" in between */
  if (req > dstlen) { /* check for condition where the dst length is too short */
    /* Two options here:
     * 1) assert(0) or return NULL to signal error
     * 2) copy as much of the path as will fit
     * It doesn't appear that the return value is actually checked anywhere mutt_concat_path()
     * is called, so we should just copy set dst to nul and let the calling function fail later.
     */
    dst[0] = 0; /* safe since we bail out early if dstlen == 0 */
    return NULL;
  }

  if (dirlen) { /* when dir is not empty */
    memcpy(dst, dir, dirlen);
    offset = dirlen;
    if (fnamelen)
      dst[offset++] = '/';
  }
  if (fnamelen) { /* when fname is not empty */
    memcpy(dst + offset, fname, fnamelen);
    offset += fnamelen;
  }
  dst[offset] = 0;
  return dst;
}