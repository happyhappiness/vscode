void init_flist(void)
{
	if (DEBUG_GTE(FLIST, 4)) {
		rprintf(FINFO, "FILE_STRUCT_LEN=%d, EXTRA_LEN=%d\n",
			(int)FILE_STRUCT_LEN, (int)EXTRA_LEN);
	}
	checksum_len = protocol_version < 21 ? 2
		     : protocol_version < 30 ? MD4_DIGEST_LEN
		     : MD5_DIGEST_LEN;
}