{
		mtree->set.mode = acs->mode_list->m_entry->mode;
		archive_string_sprintf(&setstr, " mode=%o",
		    (unsigned int)mtree->set.mode);
	}