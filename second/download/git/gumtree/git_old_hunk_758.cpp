		r = for_each_object_in_pack(p, cb, data);
		if (r)
			break;
	}
	return r ? r : pack_errors;
}
