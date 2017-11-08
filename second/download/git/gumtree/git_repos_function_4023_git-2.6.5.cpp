static long def_ff(const char *rec, long len, char *buf, long sz, void *priv)
{
	if (len > 0 &&
			(isalpha((unsigned char)*rec) || /* identifier? */
			 *rec == '_' || /* also identifier? */
			 *rec == '$')) { /* identifiers from VMS and other esoterico */
		if (len > sz)
			len = sz;
		while (0 < len && isspace((unsigned char)rec[len - 1]))
			len--;
		memcpy(buf, rec, len);
		return len;
	}
	return -1;
}