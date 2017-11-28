bool
ClientSocketContext::startOfOutput() const
{
    return http->out.size == 0;
}