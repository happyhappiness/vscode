static unsigned int readint_le(unsigned char *buf) /* must point to a
                                                      4 bytes buffer*/
{
  return ((unsigned int)buf[0]) | ((unsigned int)buf[1] << 8) |
    ((unsigned int)buf[2] << 16) | ((unsigned int)buf[3] << 24);
}