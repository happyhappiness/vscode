{
			archive_entry_unset_size(*e);
			archive_entry_copy_hardlink(*e,
			    archive_entry_pathname(le->canonical));
		}