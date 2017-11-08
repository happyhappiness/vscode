static pcre_uint16
byteflip2(pcre_uint16 value)
{
return ((value & 0x00ff) << 8) |
       ((value & 0xff00) >> 8);
}