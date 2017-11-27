static float mb_register_to_float (uint16_t hi, uint16_t lo) /* {{{ */
{
  union
  {
    uint8_t b[4];
    uint16_t s[2];
    float f;
  } conv;

#if BYTE_ORDER == LITTLE_ENDIAN
  /* little endian */
  conv.b[0] = lo & 0x00ff;
  conv.b[1] = (lo >> 8) & 0x00ff;
  conv.b[2] = hi & 0x00ff;
  conv.b[3] = (hi >> 8) & 0x00ff;
#else
  conv.b[3] = lo & 0x00ff;
  conv.b[2] = (lo >> 8) & 0x00ff;
  conv.b[1] = hi & 0x00ff;
  conv.b[0] = (hi >> 8) & 0x00ff;
#endif

  return (conv.f);
}