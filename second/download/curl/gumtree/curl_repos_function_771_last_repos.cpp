uint16_t to_u16(uint8_t b[2])
{
  uint16_t u;
  u = (b[0] << 8) + b[1];
  return u;
}