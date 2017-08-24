{
		struct isoent *np = enttbl[i];
		struct isofile *file = np->file;

		if (file->hardlink_target != NULL)
			file = file->hardlink_target;
		file->cur_content = &(file->content);
		do {
			dr_l = set_directory_record(p, WD_REMAINING,
			    np, iso9660, DIR_REC_NORMAL,
			    vdd->vdd_type);
			if (dr_l == 0) {
				memset(p, 0, WD_REMAINING);
				r = wb_consume(a, LOGICAL_BLOCK_SIZE);
				if (r < 0)
					return (r);
				p = wb = wb_buffptr(a);
				dr_l = set_directory_record(p,
				    WD_REMAINING, np, iso9660,
				    DIR_REC_NORMAL, vdd->vdd_type);
			}
			p += dr_l;
			file->cur_content = file->cur_content->next;
		} while (file->cur_content != NULL);
	}