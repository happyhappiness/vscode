void convert_to_7bit (BODY *a)
{
  if (!WithCrypto)
    return;

  while (a)
  {
    if (a->type == TYPEMULTIPART)
    {
      if (a->encoding != ENC7BIT)
      {
        a->encoding = ENC7BIT;
	convert_to_7bit(a->parts);
      }
      else if ((WithCrypto & APPLICATION_PGP) && option (OPTPGPSTRICTENC))
	convert_to_7bit (a->parts);
    } 
    else if (a->type == TYPEMESSAGE &&
	     ascii_strcasecmp(a->subtype, "delivery-status"))
    {
      if(a->encoding != ENC7BIT)
	mutt_message_to_7bit (a, NULL);
    }
    else if (a->encoding == ENC8BIT)
      a->encoding = ENCQUOTEDPRINTABLE;
    else if (a->encoding == ENCBINARY)
      a->encoding = ENCBASE64;
    else if (a->content && a->encoding != ENCBASE64 &&
	     (a->content->from || (a->content->space && 
				   option (OPTPGPSTRICTENC))))
      a->encoding = ENCQUOTEDPRINTABLE;
    a = a->next;
  }
}