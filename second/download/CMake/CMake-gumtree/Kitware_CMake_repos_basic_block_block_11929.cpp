(p[0] == 'U' && extdsize == 12) {
			/* p[1] is a minor version. */
			lha->mtime = archive_le32dec(&p[2]);
			lha->mode = archive_le16dec(&p[6]);
			lha->uid = archive_le16dec(&p[8]);
			lha->gid = archive_le16dec(&p[10]);
			lha->setflag |= UNIX_MODE_IS_SET;
		}