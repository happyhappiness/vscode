static void load_sha1_stat(struct sha1_stat *sha1_stat,
			   const struct stat_data *stat,
			   const unsigned char *sha1)
{
	stat_data_from_disk(&sha1_stat->stat, stat);
	hashcpy(sha1_stat->sha1, sha1);
	sha1_stat->valid = 1;
}