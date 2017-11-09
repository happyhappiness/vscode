struct refspec *parse_fetch_refspec(int nr_refspec, const char **refspec)
{
	return parse_refspec_internal(nr_refspec, refspec, 1, 0);
}