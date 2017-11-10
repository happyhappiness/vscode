static int verify_notes_filepair(struct diff_filepair *p, unsigned char *sha1)
{
	switch (p->status) {
	case DIFF_STATUS_MODIFIED:
		assert(p->one->mode == p->two->mode);
		assert(!is_null_sha1(p->one->sha1));
		assert(!is_null_sha1(p->two->sha1));
		break;
	case DIFF_STATUS_ADDED:
		assert(is_null_sha1(p->one->sha1));
		break;
	case DIFF_STATUS_DELETED:
		assert(is_null_sha1(p->two->sha1));
		break;
	default:
		return -1;
	}
	assert(!strcmp(p->one->path, p->two->path));
	return path_to_sha1(p->one->path, sha1);
}