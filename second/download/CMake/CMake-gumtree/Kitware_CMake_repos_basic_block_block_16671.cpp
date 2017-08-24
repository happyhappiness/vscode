(ac = acs->gid_list; ac; ac = ac->next) {
				if (ac->m_entry->gid == me->gid)
					break;
				last = ac;
			}