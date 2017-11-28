int
membercompare (stackmember a, stackmember b)
{
    /* we can compare: sub expressions to sub expressions ,
     * literals to literals
     */

    if (!((a.valuetype == ESI_EXPR_LITERAL && b.valuetype == ESI_EXPR_LITERAL &&
            a.valuestored != ESI_LITERAL_INVALID && b.valuestored != ESI_LITERAL_INVALID) ||
            (a.valuetype == ESI_EXPR_EXPR && b.valuetype == ESI_EXPR_EXPR)))
        return -2;

    if (a.valuetype == ESI_EXPR_EXPR) {
        if (a.value.integral == b.value.integral)
            return 0;
        else
            return 1;
    } else if (a.valuestored == ESI_LITERAL_STRING) {
        if (b.valuestored == ESI_LITERAL_STRING) {
            int i =strcmp (a.value.string, b.value.string);

            if (i < 0)
                return -1;

            if (i > 0)
                return 1;

            return 0;
        } else {
            /* TODO: numeric to string conversion ? */
            debugs(86, 1, "strcmp with non-string");
            return -2;
        }
    } else if (a.valuestored == ESI_LITERAL_FLOAT) {
        if (b.valuestored == ESI_LITERAL_INT) {
            if (fabs(a.value.floating - b.value.integral) < 0.00001)
                return 0;
            else if (a.value.floating < b.value.integral)
                return -1;
            else
                return 1;
        } else if (b.valuestored == ESI_LITERAL_FLOAT) {
            if (a.value.floating == b.value.floating)
                return 0;
            else if (a.value.floating < b.value.floating)
                return -1;
            else
                return 1;
        } else {
            /* TODO: attempt numeric converson again? */
            debugs(86, 1, "floatcomp with non float or int");
            return -2;
        }
    } else if (a.valuestored == ESI_LITERAL_INT) {
        if (b.valuestored == ESI_LITERAL_INT) {
            if (a.value.integral == b.value.integral)
                return 0;
            else if (a.value.integral < b.value.integral)
                return -1;
            else
                return 1;
        } else if (b.valuestored == ESI_LITERAL_FLOAT) {
            if (fabs(a.value.integral - b.value.floating) < 0.00001)
                return 0;
            else if (a.value.integral < b.value.floating)
                return -1;
            else
                return 1;
        } else {
            /* TODO: attempt numeric converson again? */
            debugs(86, 1, "intcomp vs non float non int");
            return -2;
        }
    }

    return -2;
}