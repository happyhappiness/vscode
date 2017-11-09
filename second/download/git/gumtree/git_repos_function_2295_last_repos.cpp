int has_sha1_file_with_flags(const unsigned char *sha1, int flags)
{
	if (!startup_info->have_repository)
		return 0;
	return sha1_object_info_extended(sha1, NULL,
					 flags | OBJECT_INFO_SKIP_CACHED) >= 0;
}