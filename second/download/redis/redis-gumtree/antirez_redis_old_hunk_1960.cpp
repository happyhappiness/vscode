	return (ret.p);
}

static bool
prof_flush(bool propagate_err)
{
	bool ret = false;
	ssize_t err;
