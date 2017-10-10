	 * We are about to tell the caller where they can locate the
	 * requested object.  We better make sure the packfile is
	 * still here and can be accessed before supplying that
	 * answer, as it may have been deleted since the index was
	 * loaded!
	 */
	if (!is_pack_valid(p))
		return 0;
	e->offset = offset;
	e->p = p;
	hashcpy(e->sha1, sha1);
	return 1;
}

