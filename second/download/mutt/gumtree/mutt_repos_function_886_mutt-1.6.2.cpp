char *fgetconvs (char *buf, size_t l, FGETCONV *_fc)
{
  int c;
  size_t r;
  
  for (r = 0; r + 1 < l;)
  {
    if ((c = fgetconv (_fc)) == EOF)
      break;
    buf[r++] = (char) c;
    if (c == '\n') 
      break;
  }
  buf[r] = '\0';
  
  if (r) 
    return buf;
  else 
    return NULL;
}