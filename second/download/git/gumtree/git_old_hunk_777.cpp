
	if (o->merge_size != 1)
		return error("Cannot do a bind merge of %d trees",
			     o->merge_size);
	if (a && old)
		return o->gently ? -1 :
			error(ERRORMSG(o, ERROR_BIND_OVERLAP), a->name, old->name);
	if (!a)
		return keep_entry(old, o);
	else
		return merged_entry(a, NULL, o);
}

