void
ESIVariableProcessor::identifyFunction()
{
    delete currentFunction;
    currentFunction = ESIFunction::GetFunction (&string[pos], *this);

    if (!currentFunction) {
        state = LOOKFORSTART;
    } else {
        state = 2; /* process a function */
        /* advance past function name */
        var_pos = ++pos;
    }
}