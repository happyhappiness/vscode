int
addmember (stackmember * stack, int *stackdepth, stackmember * candidate)
{
    if (candidate->valuetype != ESI_EXPR_LITERAL && *stackdepth > 1) {
        /* !(!(a==b))) is why thats safe */
        /* strictly less than until we unwind */

        if (candidate->precedence < stack[*stackdepth - 1].precedence ||
                candidate->precedence < stack[*stackdepth - 2].precedence) {
            /* must be an operator */

            if (stack[*stackdepth - 2].valuetype == ESI_EXPR_LITERAL ||
                    stack[*stackdepth - 2].valuetype == ESI_EXPR_INVALID ||
                    stack[*stackdepth - 2].eval (stack, stackdepth,
                                                 *stackdepth - 2, candidate)) {
                /* cleanup candidate and stack */
                dumpstack (stack, *stackdepth);
                cleanmember (candidate);
                debugs(86, 1, "invalid expression");
                return 0;
            }
        } else {
            stack[(*stackdepth)++] = *candidate;
        }
    } else if (candidate->valuetype != ESI_EXPR_INVALID)
        stack[(*stackdepth)++] = *candidate;

    return 1;
}