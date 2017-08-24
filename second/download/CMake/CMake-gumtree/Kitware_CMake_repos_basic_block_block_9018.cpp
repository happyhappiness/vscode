{
		memmove(&(ids->ids[i+1]), &(ids->ids[i]),
		    (ids->count - i) * sizeof(ids->ids[0]));
		ids->ids[i] = id;
		ids->count++;
	}