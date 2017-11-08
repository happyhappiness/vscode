static
void initUpdatePosition(const ENCODING *enc, const char *ptr,
			const char *end, POSITION *pos)
{
  normal_updatePosition(&utf8_encoding.enc, ptr, end, pos);
}