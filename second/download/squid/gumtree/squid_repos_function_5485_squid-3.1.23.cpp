void
cleanmember (stackmember * s)
{
    if (s->valuetype == ESI_EXPR_LITERAL
            && s->valuestored == ESI_LITERAL_STRING) {
        safe_free (s->value.string);
        s->value.string = NULL;
    }

}