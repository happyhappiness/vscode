static void stat_data_from_disk(struct stat_data *to, const unsigned char *data)
{
	memcpy(to, data, sizeof(*to));
	to->sd_ctime.sec  = ntohl(to->sd_ctime.sec);
	to->sd_ctime.nsec = ntohl(to->sd_ctime.nsec);
	to->sd_mtime.sec  = ntohl(to->sd_mtime.sec);
	to->sd_mtime.nsec = ntohl(to->sd_mtime.nsec);
	to->sd_dev	  = ntohl(to->sd_dev);
	to->sd_ino	  = ntohl(to->sd_ino);
	to->sd_uid	  = ntohl(to->sd_uid);
	to->sd_gid	  = ntohl(to->sd_gid);
	to->sd_size	  = ntohl(to->sd_size);
}