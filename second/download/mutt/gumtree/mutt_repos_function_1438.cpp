static int check_attachment_marker (char *p)
{
  char *q = AttachmentMarker;
  
  for (;*p == *q && *q && *p && *q != '\a' && *p != '\a'; p++, q++)
    ;
  return (int) (*p - *q);
}