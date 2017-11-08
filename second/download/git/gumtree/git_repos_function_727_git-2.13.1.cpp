static void prepare_header(struct archiver_args *args,
			   struct ustar_header *header,
			   unsigned int mode, unsigned long size)
{
	xsnprintf(header->mode, sizeof(header->mode), "%07o", mode & 07777);
	xsnprintf(header->size, sizeof(header->size), "%011lo", S_ISREG(mode) ? size : 0);
	xsnprintf(header->mtime, sizeof(header->mtime), "%011lo", (unsigned long) args->time);

	xsnprintf(header->uid, sizeof(header->uid), "%07o", 0);
	xsnprintf(header->gid, sizeof(header->gid), "%07o", 0);
	strlcpy(header->uname, "root", sizeof(header->uname));
	strlcpy(header->gname, "root", sizeof(header->gname));
	xsnprintf(header->devmajor, sizeof(header->devmajor), "%07o", 0);
	xsnprintf(header->devminor, sizeof(header->devminor), "%07o", 0);

	memcpy(header->magic, "ustar", 6);
	memcpy(header->version, "00", 2);

	xsnprintf(header->chksum, sizeof(header->chksum), "%07o", ustar_header_chksum(header));
}