ESIFunction *
ESIFunction::GetFunction(char const *symbol, ESIVariableProcessor &aProcessor)
{
    if (*symbol == '(')
        return new ESIFunction(aProcessor);

    return NULL;
}