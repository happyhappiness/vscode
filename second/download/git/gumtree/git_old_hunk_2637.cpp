	}
	if (adjust_shared_perm(git_HEAD)) {
		error("Unable to fix permissions on %s", lockpath);
	error_unlink_return:
		unlink_or_warn(lockpath);
	error_free_return:
		free(git_HEAD);
		return -1;
	}

#ifndef NO_SYMLINK_HEAD
	done:
#endif
	if (logmsg && !read_ref(refs_heads_master, new_sha1))
		log_ref_write(ref_target, old_sha1, new_sha1, logmsg);

	free(git_HEAD);
	return 0;
}

struct read_ref_at_cb {
