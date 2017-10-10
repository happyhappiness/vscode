			goto out;
		ret = errno;
	}
	unlink_or_warn(tmpfile);
	if (ret) {
		if (ret != EEXIST) {
			return error_errno("unable to write sha1 filename %s", filename);
		}
		/* FIXME!!! Collision check here ? */
	}

out:
	if (adjust_shared_perm(filename))
