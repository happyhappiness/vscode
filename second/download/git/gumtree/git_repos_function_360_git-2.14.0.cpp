static struct cache_entry *cache_entry_from_ondisk(struct ondisk_cache_entry *ondisk,
						   unsigned int flags,
						   const char *name,
						   size_t len)
{
	struct cache_entry *ce = xmalloc(cache_entry_size(len));

	ce->ce_stat_data.sd_ctime.sec = get_be32(&ondisk->ctime.sec);
	ce->ce_stat_data.sd_mtime.sec = get_be32(&ondisk->mtime.sec);
	ce->ce_stat_data.sd_ctime.nsec = get_be32(&ondisk->ctime.nsec);
	ce->ce_stat_data.sd_mtime.nsec = get_be32(&ondisk->mtime.nsec);
	ce->ce_stat_data.sd_dev   = get_be32(&ondisk->dev);
	ce->ce_stat_data.sd_ino   = get_be32(&ondisk->ino);
	ce->ce_mode  = get_be32(&ondisk->mode);
	ce->ce_stat_data.sd_uid   = get_be32(&ondisk->uid);
	ce->ce_stat_data.sd_gid   = get_be32(&ondisk->gid);
	ce->ce_stat_data.sd_size  = get_be32(&ondisk->size);
	ce->ce_flags = flags & ~CE_NAMEMASK;
	ce->ce_namelen = len;
	ce->index = 0;
	hashcpy(ce->oid.hash, ondisk->sha1);
	memcpy(ce->name, name, len);
	ce->name[len] = '\0';
	return ce;
}