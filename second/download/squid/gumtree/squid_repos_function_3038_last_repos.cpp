bool
ConnStateData::handleReadData()
{
    // if we are reading a body, stuff data into the body pipe
    if (bodyPipe != NULL)
        return handleRequestBodyData();
    return true;
}