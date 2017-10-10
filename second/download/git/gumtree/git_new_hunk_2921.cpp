			strbuf_release(&sb);
		}
		else {
			/* we can borrow from the file in the work tree */
			temp->name = name;
			if (!one->sha1_valid)
				sha1_to_hex_r(temp->hex, null_sha1);
			else
				sha1_to_hex_r(temp->hex, one->sha1);
			/* Even though we may sometimes borrow the
			 * contents from the work tree, we always want
			 * one->mode.  mode is trustworthy even when
			 * !(one->sha1_valid), as long as
			 * DIFF_FILE_VALID(one).
			 */
			xsnprintf(temp->mode, sizeof(temp->mode), "%06o", one->mode);
		}
		return temp;
	}
	else {
		if (diff_populate_filespec(one, 0))
			die("cannot read data blob for %s", one->path);
