(a->setflag & TIME_IS_SET) {
		r = time_excluded(a, entry);
		if (r != 0)
			return (r);
	}