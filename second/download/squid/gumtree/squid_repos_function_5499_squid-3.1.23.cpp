int evalstartexpr
(stackmember * stack, int *depth, int whereAmI, stackmember * candidate)
{
    /* debugs(86, 1, "?("); */

    if (whereAmI != *depth - 2)
        /* invalid stack */
        return 1;

    /* Only valid when RHS is an end bracket */
    if (candidate->valuetype != ESI_EXPR_END)
        return 1;

    --(*depth);

    stack[whereAmI] = stack[(*depth)];

    cleanmember (candidate);

    return 0;
}