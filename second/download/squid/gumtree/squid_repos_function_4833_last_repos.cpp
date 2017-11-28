bool
Http::Stream::startOfOutput() const
{
    return http->out.size == 0;
}