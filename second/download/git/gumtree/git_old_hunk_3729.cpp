				p->status = DIFF_STATUS_MODIFIED;
			else if (--p->one->rename_used > 0)
				p->status = DIFF_STATUS_COPIED;
			else
				p->status = DIFF_STATUS_RENAMED;
		}
		else if (hashcmp(p->one->sha1, p->two->sha1) ||
			 p->one->mode != p->two->mode ||
			 p->one->dirty_submodule ||
			 p->two->dirty_submodule ||
			 is_null_sha1(p->one->sha1))
			p->status = DIFF_STATUS_MODIFIED;
		else {
			/* This is a "no-change" entry and should not
			 * happen anymore, but prepare for broken callers.
			 */
			error("feeding unmodified %s to diffcore",
