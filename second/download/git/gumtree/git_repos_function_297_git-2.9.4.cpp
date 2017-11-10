void fill_stat_data(struct stat_data *sd, struct stat *st)
{
	sd->sd_ctime.sec = (unsigned int)st->st_ctime;
	sd->sd_mtime.sec = (unsigned int)st->st_mtime;
	sd->sd_ctime.nsec = ST_CTIME_NSEC(*st);
	sd->sd_mtime.nsec = ST_MTIME_NSEC(*st);
	sd->sd_dev = st->st_dev;
	sd->sd_ino = st->st_ino;
	sd->sd_uid = st->st_uid;
	sd->sd_gid = st->st_gid;
	sd->sd_size = st->st_size;
}