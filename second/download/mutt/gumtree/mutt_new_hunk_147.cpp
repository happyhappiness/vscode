 * This routine verifies a  "multipart/signed"  body.
 */

int mutt_signed_handler (BODY *a, STATE *s)
{
  char tempfile[_POSIX_PATH_MAX];
  int signed_type;
  int inconsistent = 0;
  
  BODY *b = a;
  BODY **signatures = NULL;
  int sigcnt = 0;
  int i;
  short goodsig = 1;
  int rc = 0;

  if (!WithCrypto)
    return -1;

  a = a->parts;
  signed_type = mutt_is_multipart_signed (b);
  if (!signed_type)
  {
    /* A null protocol value is already checked for in mutt_body_handler() */
    state_printf (s, _("[-- Error: "
                       "Unknown multipart/signed protocol %s! --]\n\n"),
                  mutt_get_parameter ("protocol", b->parameter));
    return mutt_body_handler (a, s);
  }

  if (!(a && a->next))
    inconsistent = 1;
  else
  {
    switch (signed_type)
    {
      case SIGN:
        if (a->next->type != TYPEMULTIPART ||
            ascii_strcasecmp (a->next->subtype, "mixed"))
          inconsistent = 1;
        break;
      case PGPSIGN:
        if (a->next->type != TYPEAPPLICATION ||
            ascii_strcasecmp (a->next->subtype, "pgp-signature"))
          inconsistent = 1;
        break;
      case SMIMESIGN:
        if (a->next->type != TYPEAPPLICATION ||
            (ascii_strcasecmp (a->next->subtype, "x-pkcs7-signature") &&
             ascii_strcasecmp (a->next->subtype, "pkcs7-signature")))
          inconsistent = 1;
        break;
      default:
        inconsistent = 1;
    }
  }
  if (inconsistent)
  {
    state_attach_puts (_("[-- Error: "
                         "Inconsistent multipart/signed structure! --]\n\n"),
                       s);
    return mutt_body_handler (a, s);
  }

  if (s->flags & M_DISPLAY)
  {
    
    crypt_fetch_signatures (&signatures, a->next, &sigcnt);
    
    if (sigcnt)
