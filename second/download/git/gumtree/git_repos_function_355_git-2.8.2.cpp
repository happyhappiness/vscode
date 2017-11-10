static char *copy_cache_entry_to_ondisk(struct ondisk_cache_entry *ondisk,
				       struct cache_entry *ce)
{
	short flags;

	ondisk->ctime.sec = htonl(ce->ce_stat_data.sd_ctime.sec);
	ondisk->mtime.sec = htonl(ce->ce_stat_data.sd_mtime.sec);
	ondisk->ctime.nsec = htonl(ce->ce_stat_data.sd_ctime.nsec);
	ondisk->mtime.nsec = htonl(ce->ce_stat_data.sd_mtime.nsec);
	ondisk->dev  = htonl(ce->ce_stat_data.sd_dev);
	ondisk->ino  = htonl(ce->ce_stat_data.sd_ino);
	ondisk->mode = htonl(ce->ce_mode);
	ondisk->uid  = htonl(ce->ce_stat_data.sd_uid);
	ondisk->gid  = htonl(ce->ce_stat_data.sd_gid);
	ondisk->size = htonl(ce->ce_stat_data.sd_size);
	hashcpy(ondisk->sha1, ce->sha1);

	flags = ce->ce_flags & ~CE_NAMEMASK;
	flags |= (ce_namelen(ce) >= CE_NAMEMASK ? CE_NAMEMASK : ce_namelen(ce));
	ondisk->flags = htons(flags);
	if (ce->ce_flags & CE_EXTENDED) {
		struct ondisk_cache_entry_extended *ondisk2;
		ondisk2 = (struct ondisk_cache_entry_extended *)ondisk;
		ondisk2->flags2 = htons((ce->ce_flags & CE_EXTENDED_FLAGS) >> 16);
		return ondisk2->name;
	}
	else {
		return ondisk->name;
	}
}