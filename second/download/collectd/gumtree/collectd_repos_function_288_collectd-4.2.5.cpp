double ntohd (double d)
{
	union
	{
		uint8_t  byte[8];
		uint64_t integer;
		double   floating;
	} ret;

	ret.floating = d;

	/* NAN in x86 byte order */
	if ((ret.byte[0] == 0x00) && (ret.byte[1] == 0x00)
			&& (ret.byte[2] == 0x00) && (ret.byte[3] == 0x00)
			&& (ret.byte[4] == 0x00) && (ret.byte[5] == 0x00)
			&& (ret.byte[6] == 0xf8) && (ret.byte[7] == 0x7f))
	{
		return (NAN);
	}
	else
	{
		uint64_t tmp;

		tmp = ret.integer;
		ret.integer = FP_CONVERT (tmp);
		return (ret.floating);
	}
}