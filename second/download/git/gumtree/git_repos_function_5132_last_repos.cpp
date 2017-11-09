static const char *bits_to_msg(unsigned seen_bits)
{
	switch (seen_bits) {
	case 0:
		return "no corresponding .idx or .pack";
	case PACKDIR_FILE_GARBAGE:
		return "garbage found";
	case PACKDIR_FILE_PACK:
		return "no corresponding .idx";
	case PACKDIR_FILE_IDX:
		return "no corresponding .pack";
	case PACKDIR_FILE_PACK|PACKDIR_FILE_IDX:
	default:
		return NULL;
	}
}