(ac = acs->mode_list; ac; ac = ac->next) {
				if (ac->m_entry->mode == me->mode)
					break;
				last = ac;
			}