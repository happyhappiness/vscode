{
	/*
	 * Technically, GNU tar considers a field to be in base-256
	 * only if the first byte is 0xff or 0x80.
	 */
	if (*p & 0x80)
		return (tar_atol256(p, char_cnt));
	return (tar_atol8(p, char_cnt));
}