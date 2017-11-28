void
Adaptation::Message::set(Header *aHeader)
{
    clear();
    if (aHeader) {
        header = aHeader;
        HTTPMSGLOCK(header);
        body_pipe = header->body_pipe;
    }
}