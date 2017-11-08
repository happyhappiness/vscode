static void stat_data_to_disk(struct stat_data *to, const struct stat_data *from)
{
	to->sd_ctime.sec  = htonl(from->sd_ctime.sec);
	to->sd_ctime.nsec = htonl(from->sd_ctime.nsec);
	to->sd_mtime.sec  = htonl(from->sd_mtime.sec);
	to->sd_mtime.nsec = htonl(from->sd_mtime.nsec);
	to->sd_dev	  = htonl(from->sd_dev);
	to->sd_ino	  = htonl(from->sd_ino);
	to->sd_uid	  = htonl(from->sd_uid);
	to->sd_gid	  = htonl(from->sd_gid);
	to->sd_size	  = htonl(from->sd_size);
}