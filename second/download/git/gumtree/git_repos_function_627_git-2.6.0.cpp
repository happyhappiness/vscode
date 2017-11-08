static void prepare_header(struct archiver_args *args,
			   struct ustar_header *header,
			   unsigned int mode, unsigned long size)
{
	sprintf(header->mode, "%07o", mode & 07777);
	sprintf(header->size, "%011lo", S_ISREG(mode) ? size : 0);
	sprintf(header->mtime, "%011lo", (unsigned long) args->time);

	sprintf(header->uid, "%07o", 0);
	sprintf(header->gid, "%07o", 0);
	strlcpy(header->uname, "root", sizeof(header->uname));
	strlcpy(header->gname, "root", sizeof(header->gname));
	sprintf(header->devmajor, "%07o", 0);
	sprintf(header->devminor, "%07o", 0);

	memcpy(header->magic, "ustar", 6);
	memcpy(header->version, "00", 2);

	sprintf(header->chksum, "%07o", ustar_header_chksum(header));
}