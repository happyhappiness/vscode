ESIElement::Pointer
ESIContext::ParserState::top()
{
    return stack[stackdepth-1];
}