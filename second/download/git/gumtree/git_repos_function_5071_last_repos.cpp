static void add_refspec(const char *ref)
{
	refspec_nr++;
	ALLOC_GROW(refspec, refspec_nr, refspec_alloc);
	refspec[refspec_nr-1] = ref;
}