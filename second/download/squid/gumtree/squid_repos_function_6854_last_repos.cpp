int
evalexpr(stackmember * stack, int *depth, int whereAmI, stackmember * candidate)
{
    debugs(86, DBG_IMPORTANT, "attempt to evaluate a sub-expression result");
    /* sub-scpr's can't be evaluated */
    return 1;
}