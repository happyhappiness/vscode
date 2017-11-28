std::ostream &
Ssl::operator <<(std::ostream &os, const Ssl::PeerConnectorAnswer &answer)
{
    return os << answer.conn << ", " << answer.error;
}