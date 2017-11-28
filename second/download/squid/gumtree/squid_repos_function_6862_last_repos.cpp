int
evalnotequals(stackmember * stack, int *depth, int whereAmI, stackmember * candidate)
{
    int rv;
    stackmember srv;

    if (*depth < 3)
        /* Not enough operands */
        return 1;

    if (whereAmI != *depth - 2)
        /* invalid stack */
        return 1;

    rv = membercompare(stack[whereAmI - 1], stack[whereAmI + 1]);

    if (rv == -2)
        /* invalid comparison */
        return 1;

    stackpop(stack, depth); /* arg rhs */

    stackpop(stack, depth); /* me */

    stackpop(stack, depth); /* arg lhs */

    srv.valuetype = ESI_EXPR_EXPR;

    srv.eval = evalexpr;

    srv.valuestored = ESI_LITERAL_BOOL;

    srv.value.integral = rv ? 1 : 0;

    srv.precedence = 1;

    stack[(*depth)++] = srv;

    /* we're out of way, try adding now */
    if (!addmember(stack, depth, candidate))
        /* Something wrong upstream */
        return 1;

    /* debugs(86, DBG_IMPORTANT, "?= " << srv.value.integral << " "); */
    return 0;
}