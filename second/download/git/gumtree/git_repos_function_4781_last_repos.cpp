static int verify_notes_filepair(struct diff_filepair *p, struct object_id *oid)
{
	switch (p->status) {
	case DIFF_STATUS_MODIFIED:
		assert(p->one->mode == p->two->mode);
		assert(!is_null_oid(&p->one->oid));
		assert(!is_null_oid(&p->two->oid));
		break;
	case DIFF_STATUS_ADDED:
		assert(is_null_oid(&p->one->oid));
		break;
	case DIFF_STATUS_DELETED:
		assert(is_null_oid(&p->two->oid));
		break;
	default:
		return -1;
	}
	assert(!strcmp(p->one->path, p->two->path));
	return path_to_oid(p->one->path, oid);
}