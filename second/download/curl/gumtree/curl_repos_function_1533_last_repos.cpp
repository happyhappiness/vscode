static unsigned short smb_swap16(unsigned short x)
{
  return (unsigned short) ((x << 8) | ((x >> 8) & 0xff));
}