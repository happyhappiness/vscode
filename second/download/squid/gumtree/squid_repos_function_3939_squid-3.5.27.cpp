void
Adaptation::Message::clear()
{
    HTTPMSGUNLOCK(header);
    body_pipe = NULL;
}