static void set_copy_flags (HEADER *hdr, int decode, int decrypt, int *cmflags, int *chflags)
{
  *cmflags = 0;
  *chflags = CH_UPDATE_LEN;
  
#ifdef HAVE_PGP
  if (!decode && decrypt && (hdr->pgp & PGPENCRYPT))
  {
    if (mutt_is_multipart_encrypted(hdr->content))
    {
      *chflags = CH_NONEWLINE | CH_XMIT | CH_MIME;
      *cmflags = M_CM_DECODE_PGP;
    }
    else if (mutt_is_application_pgp(hdr->content) & PGPENCRYPT)
      decode = 1;
  }
#endif

  if (decode)
  {
    *chflags = CH_XMIT | CH_MIME | CH_TXTPLAIN;
    *cmflags = M_CM_DECODE | M_CM_CHARCONV;
  }

  /* respect $weed only if decode doesn't kick in
   * for decrypt.
   */

  if (decode && !decrypt && option (OPTWEED))
  {
    *chflags |= CH_WEED;
    *cmflags |= M_CM_WEED;
  }
}