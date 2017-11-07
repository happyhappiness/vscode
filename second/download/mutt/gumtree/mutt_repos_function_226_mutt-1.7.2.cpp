static void set_copy_flags (HEADER *hdr, int decode, int decrypt, int *cmflags, int *chflags)
{
  *cmflags = 0;
  *chflags = CH_UPDATE_LEN;
  
  if (WithCrypto && !decode && decrypt && (hdr->security & ENCRYPT))
  {
    if ((WithCrypto & APPLICATION_PGP)
        && mutt_is_multipart_encrypted(hdr->content))
    {
      *chflags = CH_NONEWLINE | CH_XMIT | CH_MIME;
      *cmflags = MUTT_CM_DECODE_PGP;
    }
    else if ((WithCrypto & APPLICATION_PGP)
              && mutt_is_application_pgp (hdr->content) & ENCRYPT)
      decode = 1;
    else if ((WithCrypto & APPLICATION_SMIME)
             && mutt_is_application_smime(hdr->content) & ENCRYPT)
    {
      *chflags = CH_NONEWLINE | CH_XMIT | CH_MIME;
      *cmflags = MUTT_CM_DECODE_SMIME;
    }
  }

  if (decode)
  {
    *chflags = CH_XMIT | CH_MIME | CH_TXTPLAIN;
    *cmflags = MUTT_CM_DECODE | MUTT_CM_CHARCONV;

    if (!decrypt)	/* If decode doesn't kick in for decrypt, */
    {
      *chflags |= CH_DECODE;	/* then decode RFC 2047 headers, */

      if (option (OPTWEED))
      {
	*chflags |= CH_WEED;	/* and respect $weed. */
	*cmflags |= MUTT_CM_WEED;
      }
    }
  }
}