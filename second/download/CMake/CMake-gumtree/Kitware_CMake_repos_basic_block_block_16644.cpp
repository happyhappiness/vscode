(oldkeys & (F_UNAME | F_UID)) {
			if (acs->uid_list->count < 2 ||
			    mtree->set.uid == acs->uid_list->m_entry->uid)
				effkeys &= ~(F_UNAME | F_UID);
		}