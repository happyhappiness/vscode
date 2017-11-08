void Curl_write16_le(const short value, unsigned char *buffer)
{
  buffer[0] = (char)(value & 0x00FF);
  buffer[1] = (char)((value & 0xFF00) >> 8);
}