static unsigned __int64 smb_swap64(unsigned __int64 x)
{
  return ((unsigned __int64)smb_swap32(x) << 32) | smb_swap32(x >> 32);
}