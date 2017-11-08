static unsigned long long smb_swap64(unsigned long long x)
{
  return ((unsigned long long)smb_swap32(x) << 32) | smb_swap32(x >> 32);
}