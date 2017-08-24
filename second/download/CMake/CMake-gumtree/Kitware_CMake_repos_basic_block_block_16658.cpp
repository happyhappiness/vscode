{
	struct attr_counter *ac, *last;
	struct att_counter_set *acs = &mtree->acs;
	int keys = mtree->keys;

	if (keys & (F_UNAME | F_UID)) {
		if (acs->uid_list == NULL) {
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
	}
	if (keys & (F_GNAME | F_GID)) {
		if (acs->gid_list == NULL) {
			acs->gid_list = attr_counter_new(me, NULL);
			if (acs->gid_list == NULL)
				return (-1);
		} else {
			last = NULL;
			for (ac = acs->gid_list; ac; ac = ac->next) {
				if (ac->m_entry->gid == me->gid)
					break;
				last = ac;
			}
			if (attr_counter_inc(&acs->gid_list, ac, last, me) < 0)
				return (-1);
		}
	}
	if (keys & F_MODE) {
		if (acs->mode_list == NULL) {
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
	}
	if (keys & F_FLAGS) {
		if (acs->flags_list == NULL) {
			acs->flags_list = attr_counter_new(me, NULL);
			if (acs->flags_list == NULL)
				return (-1);
		} else {
			last = NULL;
			for (ac = acs->flags_list; ac; ac = ac->next) {
				if (ac->m_entry->fflags_set == me->fflags_set &&
				    ac->m_entry->fflags_clear ==
							me->fflags_clear)
					break;
				last = ac;
			}
			if (attr_counter_inc(&acs->flags_list, ac, last, me) < 0)
				return (-1);
		}
	}

	return (0);
}