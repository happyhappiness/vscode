static int
get_label_uuid(const char *device, char **label, char *uuid)
{
	/* start with ext2 and xfs tests, taken from mount_guess_fstype */
	/* should merge these later */
	int fd, rv = 1;
	size_t namesize;
	struct ext2_super_block e2sb;
#if HAVE_XFS_XQM_H
	struct xfs_super_block xfsb;
#endif
	struct reiserfs_super_block reisersb;

	fd = open(device, O_RDONLY);
	if(fd == -1) {
		return rv;
	}

	if(lseek(fd, 1024, SEEK_SET) == 1024
	&& read(fd, (char *)&e2sb, sizeof(e2sb)) == sizeof(e2sb)
	&& ext2magic(e2sb) == EXT2_SUPER_MAGIC) {
		memcpy(uuid, e2sb.s_uuid, sizeof(e2sb.s_uuid));
		namesize = sizeof(e2sb.s_volume_name);
		*label = smalloc(namesize + 1);
		sstrncpy(*label, e2sb.s_volume_name, namesize);
		rv = 0;
#if HAVE_XFS_XQM_H
	} else if(lseek(fd, 0, SEEK_SET) == 0
	&& read(fd, (char *)&xfsb, sizeof(xfsb)) == sizeof(xfsb)
	&& (strncmp((char *)&xfsb.s_magic, XFS_SUPER_MAGIC_STR, 4) == 0 ||
	strncmp((char *)&xfsb.s_magic, XFS_SUPER_MAGIC2_STR, 4) == 0)) {
		memcpy(uuid, xfsb.s_uuid, sizeof(xfsb.s_uuid));
		namesize = sizeof(xfsb.s_fsname);
		*label = smalloc(namesize + 1);
		sstrncpy(*label, xfsb.s_fsname, namesize);
		rv = 0;
#endif /* HAVE_XFS_XQM_H */
	} else if(lseek(fd, 65536, SEEK_SET) == 65536
	&& read(fd, (char *)&reisersb, sizeof(reisersb)) == sizeof(reisersb)
	&& !strncmp((char *)&reisersb.s_magic, REISER_SUPER_MAGIC, 9)) {
		memcpy(uuid, reisersb.s_uuid, sizeof(reisersb.s_uuid));
		namesize = sizeof(reisersb.s_volume_name);
		*label = smalloc(namesize + 1);
		sstrncpy(*label, reisersb.s_volume_name, namesize);
		rv = 0;
	}
	close(fd);
	return rv;
}