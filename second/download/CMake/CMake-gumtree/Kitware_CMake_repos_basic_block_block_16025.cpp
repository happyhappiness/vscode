{
		/*
		 *   "PX" Format:
		 *               len  ver
		 *    +----+----+----+----+-----------+-----------+
		 *    | 'P'| 'X'| 2C | 01 | FILE MODE |   LINKS   |
		 *    +----+----+----+----+-----------+-----------+
		 *    0    1    2    3    4          12          20
		 *    +-----------+-----------+------------------+
		 *    |  USER ID  | GROUP ID  |FILE SERIAL NUMBER|
		 *    +-----------+-----------+------------------+
		 *   20          28          36                 44
		 */
		length = 44;
		if (extra_space(&ctl) < length)
			bp = extra_next_record(&ctl, length);
		if (bp != NULL) {
			mode_t mode;
			int64_t uid;
			int64_t gid;

			mode = archive_entry_mode(file->entry);
			uid = archive_entry_uid(file->entry);
			gid = archive_entry_gid(file->entry);
			if (iso9660->opt.rr == OPT_RR_USEFUL) {
				/*
				 * This action is similar to mkisofs -r option
				 * but our rockridge=useful option does not
				 * set a zero to uid and gid.
				 */
				/* set all read bit ON */
				mode |= 0444;
#if !defined(_WIN32) && !defined(__CYGWIN__)
				if (mode & 0111)
#endif
					/* set all exec bit ON */
					mode |= 0111;
				/* clear all write bits. */
				mode &= ~0222;
				/* clear setuid,setgid,sticky bits. */
				mode &= ~07000;
			}

			bp[1] = 'P';
			bp[2] = 'X';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			/* file mode */
			set_num_733(bp+5, mode);
			/* file links (stat.st_nlink) */
			set_num_733(bp+13,
			    archive_entry_nlink(file->entry));
			set_num_733(bp+21, (uint32_t)uid);
			set_num_733(bp+29, (uint32_t)gid);
			/* File Serial Number */
			if (pxent->dir)
				set_num_733(bp+37, pxent->dir_location);
			else if (file->hardlink_target != NULL)
				set_num_733(bp+37,
				    file->hardlink_target->cur_content->location);
			else
				set_num_733(bp+37,
				    file->cur_content->location);
			bp += length;
		}
		extra_tell_used_size(&ctl, length);
	}