void write_byte(int f,unsigned char c)
{
  write_buf(f,(char *)&c,1);
}