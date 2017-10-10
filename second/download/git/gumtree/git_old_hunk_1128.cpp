							 dst_path, 0, 0);

				add_index_entry(&wtindex, ce2,
						ADD_CACHE_JUST_APPEND);

				add_path(&rdir, rdir_len, dst_path);
				if (ensure_leading_directories(rdir.buf))
					return error("could not create "
						     "directory for '%s'",
						     dst_path);
				add_path(&wtdir, wtdir_len, dst_path);
				if (symlinks) {
					if (symlink(wtdir.buf, rdir.buf)) {
						ret = error_errno("could not symlink '%s' to '%s'", wtdir.buf, rdir.buf);
						goto finish;
					}
