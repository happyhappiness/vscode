const char ** poptGetArgs(poptContext con)
{
    if (con == NULL ||
	con->leftovers == NULL || con->numLeftovers == con->nextLeftover)
	return NULL;

    /* some apps like [like RPM ;-) ] need this NULL terminated */
    con->leftovers[con->numLeftovers] = NULL;

    /*@-nullret -nullstate @*/	/* FIX: typedef double indirection. */
    return (con->leftovers + con->nextLeftover);
    /*@=nullret =nullstate @*/
}