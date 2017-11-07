int mutt_check_mime_type (const char *s)
{
  if (ascii_strcasecmp ("text", s) == 0)
    return TYPETEXT;
  else if (ascii_strcasecmp ("multipart", s) == 0)
    return TYPEMULTIPART;
#ifdef SUN_ATTACHMENT 
  else if (ascii_strcasecmp ("x-sun-attachment", s) == 0)
    return TYPEMULTIPART;
#endif
  else if (ascii_strcasecmp ("application", s) == 0)
    return TYPEAPPLICATION;
  else if (ascii_strcasecmp ("message", s) == 0)
    return TYPEMESSAGE;
  else if (ascii_strcasecmp ("image", s) == 0)
    return TYPEIMAGE;
  else if (ascii_strcasecmp ("audio", s) == 0)
    return TYPEAUDIO;
  else if (ascii_strcasecmp ("video", s) == 0)
    return TYPEVIDEO;
  else if (ascii_strcasecmp ("model", s) == 0)
    return TYPEMODEL;
  else if (ascii_strcasecmp ("*", s) == 0)
    return TYPEANY;
  else if (ascii_strcasecmp (".*", s) == 0)
    return TYPEANY;
  else
    return TYPEOTHER;
}