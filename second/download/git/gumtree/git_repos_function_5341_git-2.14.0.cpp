static void print_debug(const struct cache_entry *ce)
{
	if (debug_mode) {
		const struct stat_data *sd = &ce->ce_stat_data;

		printf("  ctime: %d:%d\n", sd->sd_ctime.sec, sd->sd_ctime.nsec);
		printf("  mtime: %d:%d\n", sd->sd_mtime.sec, sd->sd_mtime.nsec);
		printf("  dev: %d\tino: %d\n", sd->sd_dev, sd->sd_ino);
		printf("  uid: %d\tgid: %d\n", sd->sd_uid, sd->sd_gid);
		printf("  size: %d\tflags: %x\n", sd->sd_size, ce->ce_flags);
	}
}