const char *
TC_CHECK_PACKET(const IPT_CHAINLABEL chain,
		STRUCT_ENTRY *entry,
		TC_HANDLE_T *handle)
{
	iptc_fn = TC_CHECK_PACKET;
	errno = ENOSYS;
	return NULL;
}