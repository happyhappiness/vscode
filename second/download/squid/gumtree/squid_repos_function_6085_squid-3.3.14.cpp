int
evalliteral(stackmember * stack, int *depth, int whereAmI, stackmember * candidate)
{
    debugs(86, DBG_IMPORTANT, "attempt to evaluate a literal");
    /* literals can't be evaluated */
    return 1;
}