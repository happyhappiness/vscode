(archive_strlen(&(acs->uid_list->m_entry->uname)) > 0) {
			archive_strcat(&setstr, " uname=");
			mtree_quote(&setstr, acs->uid_list->m_entry->uname.s);
		} else {
			keys &= ~F_UNAME;
			if ((oldkeys & F_UNAME) != 0)
				archive_strcat(&unsetstr, " uname");
		}