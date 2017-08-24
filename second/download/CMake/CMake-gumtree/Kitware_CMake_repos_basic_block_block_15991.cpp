(tf_flags & TF_CREATION) {
				set_time_915(bp+1,
				    archive_entry_birthtime(file->entry));
				bp += 7;
			}