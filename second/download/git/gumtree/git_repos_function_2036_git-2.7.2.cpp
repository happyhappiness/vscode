static void stat_data_from_disk(struct stat_data *to, const struct stat_data *from)
{
	to->sd_ctime.sec  = get_be32(&from->sd_ctime.sec);
	to->sd_ctime.nsec = get_be32(&from->sd_ctime.nsec);
	to->sd_mtime.sec  = get_be32(&from->sd_mtime.sec);
	to->sd_mtime.nsec = get_be32(&from->sd_mtime.nsec);
	to->sd_dev	  = get_be32(&from->sd_dev);
	to->sd_ino	  = get_be32(&from->sd_ino);
	to->sd_uid	  = get_be32(&from->sd_uid);
	to->sd_gid	  = get_be32(&from->sd_gid);
	to->sd_size	  = get_be32(&from->sd_size);
}