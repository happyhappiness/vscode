(oldkeys & (F_GNAME | F_GID)) {
			if (acs->gid_list->count < 2 ||
			    mtree->set.gid == acs->gid_list->m_entry->gid)
				effkeys &= ~(F_GNAME | F_GID);
		}