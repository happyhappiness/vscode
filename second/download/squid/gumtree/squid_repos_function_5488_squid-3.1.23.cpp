int evalnegate
(stackmember * stack, int *depth, int whereAmI, stackmember * candidate)
{
    if (whereAmI != *depth - 2)
        /* invalid stack */
        return 1;

    if (stack[whereAmI + 1].valuetype != ESI_EXPR_EXPR)
        /* invalid operand */
        return 1;

    /* copy down */
    --(*depth);

    stack[whereAmI] = stack[(*depth)];

    cleanmember (candidate);

    if (stack[whereAmI].value.integral == 1)
        stack[whereAmI].value.integral = 0;
    else
        stack[whereAmI].value.integral = 1;

    return 0;
}