{
		mtree->set.uid = acs->uid_list->m_entry->uid;
		archive_string_sprintf(&setstr, " uid=%jd",
		    (intmax_t)mtree->set.uid);
	}