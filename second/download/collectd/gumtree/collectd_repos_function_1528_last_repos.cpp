static size_t varint(uint8_t buffer[static VARINT_UINT32_BYTES],
                     uint32_t value) {
  for (size_t i = 0; i < VARINT_UINT32_BYTES; i++) {
    buffer[i] = (uint8_t)(value & 0x7f);
    value >>= 7;

    if (value == 0)
      return i + 1;

    buffer[i] |= 0x80;
  }

  return 0;
}