(acs->flags_list->count < 2 ||
			    (acs->flags_list->m_entry->fflags_set ==
				mtree->set.fflags_set &&
			     acs->flags_list->m_entry->fflags_clear ==
				mtree->set.fflags_clear))
				effkeys &= ~F_FLAGS