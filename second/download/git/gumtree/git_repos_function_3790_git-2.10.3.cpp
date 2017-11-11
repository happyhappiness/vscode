static struct refspec *parse_push_refspec(int nr_refspec, const char **refspec)
{
	return parse_refspec_internal(nr_refspec, refspec, 0, 0);
}