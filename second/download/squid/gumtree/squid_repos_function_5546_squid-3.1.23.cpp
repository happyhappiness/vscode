void
ESIInclude::fail (ESIStreamContext::Pointer stream)
{
    subRequestDone (stream, false);
}