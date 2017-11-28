int
ESIExpression::Evaluate (char const *s)
{
    stackmember stack[20];
    int stackdepth = 0;
    char const *end;
    PROF_start(esiExpressionEval);

    while (*s) {
        stackmember candidate = getsymbol (s, &end);

        if (candidate.valuetype != ESI_EXPR_INVALID) {
            assert (s != end);

            if (!addmember (stack, &stackdepth, &candidate)) {
                PROF_stop(esiExpressionEval);
                return 0;
            }

            s = end;
        } else {
            assert (s == end);
            debugs(86, 1, "failed parsing expression");
            PROF_stop(esiExpressionEval);
            return 0;
        }
    }

    if (stackdepth > 1) {
        stackmember rv;
        rv.valuetype = ESI_EXPR_INVALID;
        rv.precedence = 0;

        if (stack[stackdepth - 2].
                eval (stack, &stackdepth, stackdepth - 2, &rv)) {
            /* special case - leading operator failed */
            debugs(86, 1, "invalid expression");
            PROF_stop(esiExpressionEval);
            return 0;
        }
    }

    if (stackdepth == 0) {
        /* Empty expression - evaluate to false */
        PROF_stop(esiExpressionEval);
        return 0;
    }

    /* if we hit here, we think we have a valid result */
    assert (stackdepth == 1);

    assert (stack[0].valuetype == ESI_EXPR_EXPR);

    PROF_stop(esiExpressionEval);

    return stack[0].value.integral ? 1 : 0;
}