(oldkeys & F_MODE) {
			if (acs->mode_list->count < 2 ||
			    mtree->set.mode == acs->mode_list->m_entry->mode)
				effkeys &= ~F_MODE;
		}