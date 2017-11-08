static int compare_ofs_delta_bases(off_t offset1, off_t offset2,
				   enum object_type type1,
				   enum object_type type2)
{
	int cmp = type1 - type2;
	if (cmp)
		return cmp;
	return offset1 < offset2 ? -1 :
	       offset1 > offset2 ?  1 :
	       0;
}