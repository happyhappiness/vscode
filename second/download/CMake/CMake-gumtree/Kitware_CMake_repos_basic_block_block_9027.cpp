{
		m = (t + b)>>1;
		if (ids->ids[m] == id)
			return (1);
		if (ids->ids[m] < id)
			t = m + 1;
		else
			b = m;
	}