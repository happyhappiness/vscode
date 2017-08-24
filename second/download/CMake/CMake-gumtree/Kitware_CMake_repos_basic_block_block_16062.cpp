{
		struct isoent *xisoent;
		struct isofile *file;
		unsigned char flag;

		if (t == DIR_REC_PARENT)
			xisoent = isoent->parent;
		else
			xisoent = isoent;
		file = isoent->file;
		if (file->hardlink_target != NULL)
			file = file->hardlink_target;
		/* Make a file flag. */
		if (xisoent->dir)
			flag = FILE_FLAG_DIRECTORY;
		else {
			if (file->cur_content->next != NULL)
				flag = FILE_FLAG_MULTI_EXTENT;
			else
				flag = 0;
		}

		bp = p -1;
		/* Extended Attribute Record Length */
		set_num_711(bp+2, 0);
		/* Location of Extent */
		if (xisoent->dir)
			set_num_733(bp+3, xisoent->dir_location);
		else
			set_num_733(bp+3, file->cur_content->location);
		/* Data Length */
		if (xisoent->dir)
			set_num_733(bp+11,
			    xisoent->dir_block * LOGICAL_BLOCK_SIZE);
		else
			set_num_733(bp+11, (uint32_t)file->cur_content->size);
		/* Recording Date and Time */
		/* NOTE:
		 *  If a file type is symbolic link, you are seeing this
		 *  field value is different from a value mkisofs makes.
		 *  libarchive uses lstat to get this one, but it
		 *  seems mkisofs uses stat to get.
		 */
		set_time_915(bp+19,
		    archive_entry_mtime(xisoent->file->entry));
		/* File Flags */
		bp[26] = flag;
		/* File Unit Size */
		set_num_711(bp+27, 0);
		/* Interleave Gap Size */
		set_num_711(bp+28, 0);
		/* Volume Sequence Number */
		set_num_723(bp+29, iso9660->volume_sequence_number);
		/* Length of File Identifier */
		set_num_711(bp+33, (unsigned char)fi_len);
		/* File Identifier */
		switch (t) {
		case DIR_REC_VD:
		case DIR_REC_SELF:
			set_num_711(bp+34, 0);
			break;
		case DIR_REC_PARENT:
			set_num_711(bp+34, 1);
			break;
		case DIR_REC_NORMAL:
			if (isoent->identifier != NULL)
				memcpy(bp+34, isoent->identifier, fi_len);
			else
				set_num_711(bp+34, 0);
			break;
		}
	}