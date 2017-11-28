HttpMsgParseState &operator++ (HttpMsgParseState &aState)
{
    int tmp = (int)aState;
    aState = (HttpMsgParseState)(++tmp);
    return aState;
}