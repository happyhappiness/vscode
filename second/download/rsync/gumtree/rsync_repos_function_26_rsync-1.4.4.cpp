unsigned char read_byte(int f)
{
  char c;
  read_buf(f,&c,1);
  return (unsigned char)c;
}