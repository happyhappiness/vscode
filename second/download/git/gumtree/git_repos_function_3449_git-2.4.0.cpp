int for_each_remote(each_remote_fn fn, void *priv)
{
	int i, result = 0;
	read_config();
	for (i = 0; i < remotes_nr && !result; i++) {
		struct remote *r = remotes[i];
		if (!r)
			continue;
		if (!r->fetch)
			r->fetch = parse_fetch_refspec(r->fetch_refspec_nr,
						       r->fetch_refspec);
		if (!r->push)
			r->push = parse_push_refspec(r->push_refspec_nr,
						     r->push_refspec);
		result = fn(r, priv);
	}
	return result;
}