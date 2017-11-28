void
ESIContext::ParserState::popAll()
{
    while (stackdepth)
        stack[--stackdepth] = NULL;
}