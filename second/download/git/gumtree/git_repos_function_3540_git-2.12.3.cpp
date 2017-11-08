static int merge_file_1(struct merge_options *o,
					   const struct diff_filespec *one,
					   const struct diff_filespec *a,
					   const struct diff_filespec *b,
					   const char *branch1,
					   const char *branch2,
					   struct merge_file_info *result)
{
	result->merge = 0;
	result->clean = 1;

	if ((S_IFMT & a->mode) != (S_IFMT & b->mode)) {
		result->clean = 0;
		if (S_ISREG(a->mode)) {
			result->mode = a->mode;
			oidcpy(&result->oid, &a->oid);
		} else {
			result->mode = b->mode;
			oidcpy(&result->oid, &b->oid);
		}
	} else {
		if (!oid_eq(&a->oid, &one->oid) && !oid_eq(&b->oid, &one->oid))
			result->merge = 1;

		/*
		 * Merge modes
		 */
		if (a->mode == b->mode || a->mode == one->mode)
			result->mode = b->mode;
		else {
			result->mode = a->mode;
			if (b->mode != one->mode) {
				result->clean = 0;
				result->merge = 1;
			}
		}

		if (oid_eq(&a->oid, &b->oid) || oid_eq(&a->oid, &one->oid))
			oidcpy(&result->oid, &b->oid);
		else if (oid_eq(&b->oid, &one->oid))
			oidcpy(&result->oid, &a->oid);
		else if (S_ISREG(a->mode)) {
			mmbuffer_t result_buf;
			int ret = 0, merge_status;

			merge_status = merge_3way(o, &result_buf, one, a, b,
						  branch1, branch2);

			if ((merge_status < 0) || !result_buf.ptr)
				ret = err(o, _("Failed to execute internal merge"));

			if (!ret && write_sha1_file(result_buf.ptr, result_buf.size,
						    blob_type, result->oid.hash))
				ret = err(o, _("Unable to add %s to database"),
					  a->path);

			free(result_buf.ptr);
			if (ret)
				return ret;
			result->clean = (merge_status == 0);
		} else if (S_ISGITLINK(a->mode)) {
			result->clean = merge_submodule(result->oid.hash,
						       one->path,
						       one->oid.hash,
						       a->oid.hash,
						       b->oid.hash,
						       !o->call_depth);
		} else if (S_ISLNK(a->mode)) {
			oidcpy(&result->oid, &a->oid);

			if (!oid_eq(&a->oid, &b->oid))
				result->clean = 0;
		} else
			die("BUG: unsupported object type in the tree");
	}

	return 0;
}