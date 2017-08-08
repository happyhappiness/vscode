{
		mtree->set.gid = acs->gid_list->m_entry->gid;
		archive_string_sprintf(&setstr, " gid=%jd",
		    (intmax_t)mtree->set.gid);
	}