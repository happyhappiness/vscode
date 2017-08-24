(ac = acs->flags_list; ac; ac = ac->next) {
				if (ac->m_entry->fflags_set == me->fflags_set &&
				    ac->m_entry->fflags_clear ==
							me->fflags_clear)
					break;
				last = ac;
			}