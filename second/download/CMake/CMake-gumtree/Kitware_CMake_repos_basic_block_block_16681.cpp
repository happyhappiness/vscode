(acs->uid_list == NULL) {
			acs->uid_list = attr_counter_new(me, NULL);
			if (acs->uid_list == NULL)
				return (-1);
		} else {
			last = NULL;
			for (ac = acs->uid_list; ac; ac = ac->next) {
				if (ac->m_entry->uid == me->uid)
					break;
				last = ac;
			}
			if (attr_counter_inc(&acs->uid_list, ac, last, me) < 0)
				return (-1);
		}