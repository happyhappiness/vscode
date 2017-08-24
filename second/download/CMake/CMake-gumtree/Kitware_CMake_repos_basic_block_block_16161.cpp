{
			int dr_l;

			dr_l = get_dir_rec_size(iso9660, np, DIR_REC_NORMAL,
			    vdd->vdd_type);
			if ((bs + dr_l) > LOGICAL_BLOCK_SIZE) {
				block ++;
				bs = dr_l;
			} else
				bs += dr_l;
			file->cur_content = file->cur_content->next;
		}