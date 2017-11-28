stackmember
getsymbol(const char *s, char const **endptr)
{
    stackmember rv;
    char *end;
    char const *origs = s;
    /* trim whitespace */
    s = trim(s);
    rv.eval = NULL;		/* A literal */
    rv.valuetype = ESI_EXPR_INVALID;
    rv.valuestored = ESI_LITERAL_INVALID;
    rv.precedence = 1; /* A literal */

    if (('0' <= *s && *s <= '9') || *s == '-') {
        size_t length = strspn(s, "0123456789.");
        char const *point;

        if ((point = strchr(s, '.')) && point - s < (ssize_t)length) {
            /* floating point */
            errno=0; /* reset errno */
            rv.value.floating = strtod(s, &end);

            if (s == end || errno) {
                /* Couldn't convert to float */
                debugs(86, DBG_IMPORTANT, "failed to convert '" << s << "' to float ");
                *endptr = origs;
            } else {
                debugs(86,6, "found " << rv.value.floating << " of length " << end - s);
                *endptr = end;
                rv.eval = evalliteral;
                rv.valuestored = ESI_LITERAL_FLOAT;
                rv.valuetype = ESI_EXPR_LITERAL;
                rv.precedence = 1;
            }
        } else {
            /* INT */
            errno=0; /* reset errno */
            rv.value.integral = strtol(s, &end, 0);

            if (s == end || errno) {
                /* Couldn't convert to int */
                debugs(86, DBG_IMPORTANT, "failed to convert '" << s << "' to int ");
                *endptr = origs;
            } else {
                debugs(86,6, "found " << rv.value.integral << " of length " << end - s);
                *endptr = end;
                rv.eval = evalliteral;
                rv.valuestored = ESI_LITERAL_INT;
                rv.valuetype = ESI_EXPR_LITERAL;
                rv.precedence = 1;
            }
        }
    } else if ('!' == *s) {
        if ('=' == *(s + 1)) {
            debugs(86, 6, "found !=");
            *endptr = s + 2;
            rv.eval = evalnotequals;
            rv.valuetype = ESI_EXPR_NOTEQ;
            rv.precedence = 5;
        } else {
            debugs(86, 6, "found !");
            *endptr = s + 1;
            rv.valuetype = ESI_EXPR_NOT;
            rv.precedence = 4;
            rv.eval = evalnegate;
        }
    } else if ('\'' == *s) {
        char const *t = s + 1;
        debugs(86, 6, "found \'");

        while (*t != '\'' && *t)
            ++t;

        if (!*t) {
            debugs(86, DBG_IMPORTANT, "missing end \' in '" << s << "'");
            *endptr = origs;
        } else {
            *endptr = t + 1;
            /* Special case for zero length strings */

            if (t - s - 1)
                rv.value.string = xstrndup(s + 1, t - s - 1);
            else
                rv.value.string = static_cast<char *>(xcalloc(1,1));

            rv.eval = evalliteral;

            rv.valuestored = ESI_LITERAL_STRING;

            rv.valuetype = ESI_EXPR_LITERAL;

            rv.precedence = 1;

            debugs(86, 6, "found  string '" << rv.value.string << "'");
        }
    } else if ('(' == *s) {
        debugs(86, 6, "found subexpr start");
        *endptr = s + 1;
        rv.valuetype = ESI_EXPR_START;
        rv.precedence = 5;
        rv.eval = evalstartexpr;
    } else if (')' == *s) {
        debugs(86, 6, "found subexpr end");
        *endptr = s + 1;
        rv.valuetype = ESI_EXPR_END;
        rv.precedence = 0;
        rv.eval = evalendexpr;
    } else if ('&' == *s) {
        debugs(86, 6, "found AND");
        *endptr = s + 1;
        rv.valuetype = ESI_EXPR_AND;
        rv.precedence = 3;
        rv.eval = evaland;
    } else if ('|' == *s) {
        debugs(86, 6, "found OR");
        *endptr = s + 1;
        rv.valuetype = ESI_EXPR_OR;
        rv.precedence = 2;
        rv.eval = evalor;
    } else if ('=' == *s) {
        if ('=' == *(s + 1)) {
            debugs(86, 6, "found equals");
            *endptr = s + 2;
            rv.valuetype = ESI_EXPR_EQ;
            rv.precedence = 5;
            rv.eval = evalequals;
        } else {
            debugs(86, DBG_IMPORTANT, "invalid expr '" << s << "'");
            *endptr = origs;
        }
    } else if ('<' == *s) {
        if ('=' == *(s + 1)) {
            debugs(86, 6, "found less-equals");
            *endptr = s + 2;
            rv.valuetype = ESI_EXPR_LESSEQ;
            rv.precedence = 5;
            rv.eval = evallesseq;
        } else {
            debugs(86, 6, "found less than");
            *endptr = s + 1;
            rv.valuetype = ESI_EXPR_LESS;
            rv.precedence = 5;
            rv.eval = evallessthan;
        }
    } else if ('>' == *s) {
        if ('=' == *(s + 1)) {
            debugs(86, 6, "found more-equals");
            *endptr = s + 2;
            rv.valuetype = ESI_EXPR_MOREEQ;
            rv.precedence = 5;
            rv.eval = evalmoreeq;
        } else {
            debugs(86, 6, "found more than");
            *endptr = s + 1;
            rv.valuetype = ESI_EXPR_MORE;
            rv.precedence = 5;
            rv.eval = evalmorethan;
        }
    } else if (!strncmp(s, "false", 5)) {
        debugs(86, 5, "getsymbol: found variable result 'false'");
        *endptr = s + 5;
        rv.valuetype = ESI_EXPR_EXPR;
        rv.valuestored = ESI_LITERAL_BOOL;
        rv.value.integral = 0;
        rv.precedence = 1;
        rv.eval = evalexpr;
    } else if (!strncmp(s, "true", 4)) {
        debugs(86, 5, "getsymbol: found variable result 'true'");
        *endptr = s + 4;
        rv.valuetype = ESI_EXPR_EXPR;
        rv.valuestored = ESI_LITERAL_BOOL;
        rv.value.integral = 1;
        rv.precedence = 1;
        rv.eval = evalexpr;
    } else {
        debugs(86, DBG_IMPORTANT, "invalid expr '" << s << "'");
        *endptr = origs;
    }

    return rv;
}