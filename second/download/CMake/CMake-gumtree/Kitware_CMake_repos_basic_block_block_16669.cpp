(acs->mode_list == NULL) {
			acs->mode_list = attr_counter_new(me, NULL);
			if (acs->mode_list == NULL)
				return (-1);
		} else {
			last = NULL;
			for (ac = acs->mode_list; ac; ac = ac->next) {
				if (ac->m_entry->mode == me->mode)
					break;
				last = ac;
			}
			if (attr_counter_inc(&acs->mode_list, ac, last, me) < 0)
				return (-1);
		}