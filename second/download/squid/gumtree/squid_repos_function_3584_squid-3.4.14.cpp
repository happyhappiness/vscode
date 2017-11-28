bool
ConnStateData::handleReadData(char *buf, size_t size)
{
    char *current_buf = in.addressToReadInto();

    if (buf != current_buf)
        memmove(current_buf, buf, size);

    in.notYetUsed += size;

    in.buf[in.notYetUsed] = '\0'; /* Terminate the string */

    // if we are reading a body, stuff data into the body pipe
    if (bodyPipe != NULL)
        return handleRequestBodyData();
    return true;
}