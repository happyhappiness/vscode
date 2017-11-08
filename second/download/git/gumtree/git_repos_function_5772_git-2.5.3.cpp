int uname(struct utsname *buf)
{
	DWORD v = GetVersion();
	memset(buf, 0, sizeof(*buf));
	strcpy(buf->sysname, "Windows");
	sprintf(buf->release, "%u.%u", v & 0xff, (v >> 8) & 0xff);
	/* assuming NT variants only.. */
	sprintf(buf->version, "%u", (v >> 16) & 0x7fff);
	return 0;
}