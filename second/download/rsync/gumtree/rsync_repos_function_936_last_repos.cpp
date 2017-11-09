static inline /*@null@*/ void *
_free(/*@only@*/ /*@null@*/ const void * p)
	/*@modifies p @*/
{
    if (p != NULL)	free((void *)p);
    return NULL;
}