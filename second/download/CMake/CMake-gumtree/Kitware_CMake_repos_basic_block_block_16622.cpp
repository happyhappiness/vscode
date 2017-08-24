(archive_strlen(&(acs->gid_list->m_entry->gname)) > 0) {
			archive_strcat(&setstr, " gname=");
			mtree_quote(&setstr, acs->gid_list->m_entry->gname.s);
		} else {
			keys &= ~F_GNAME;
			if ((oldkeys & F_GNAME) != 0)
				archive_strcat(&unsetstr, " gname");
		}