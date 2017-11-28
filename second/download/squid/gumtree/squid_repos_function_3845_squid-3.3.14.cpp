void
Adaptation::Message::set(Header *aHeader)
{
    clear();
    if (aHeader) {
        header = HTTPMSGLOCK(aHeader);
        body_pipe = header->body_pipe;
    }
}