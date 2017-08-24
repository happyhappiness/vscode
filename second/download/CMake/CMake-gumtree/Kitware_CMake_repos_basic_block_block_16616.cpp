{
			archive_strcat(&setstr, " flags=");
			mtree_quote(&setstr,
			    acs->flags_list->m_entry->fflags_text.s);
			mtree->set.fflags_set =
			    acs->flags_list->m_entry->fflags_set;
			mtree->set.fflags_clear =
			    acs->flags_list->m_entry->fflags_clear;
		}