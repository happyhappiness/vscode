static bool
EvalBoolExpr(const char* expr)
{
    assert(expr != NULL);
    if (strcmp(expr, "true") == 0) {
        return true;
    } else if (strcmp(expr, "false") == 0) {
        return false;
    } else if (const char* equation = strchr(expr, '=')) {
        const char* rvalue = skip_ws(equation + 1);
        char* lvalue = (char*)xmalloc(equation - expr + 1);
        xstrncpy(lvalue, expr, equation - expr + 1);
        trim_trailing_ws(lvalue);

        long number1;
        if (!StrToInt(lvalue, number1))
            fatalf("String is not a integer number: '%s'\n", lvalue);
        long number2;
        if (!StrToInt(rvalue, number2))
            fatalf("String is not a integer number: '%s'\n", rvalue);

        xfree(lvalue);
        return number1 == number2;
    }
    fatalf("Unable to evaluate expression '%s'\n", expr);
    return false; // this place cannot be reached
}