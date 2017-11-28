std::ostream& Snmp::operator << (std::ostream& os, const Response& response)
{
    os << "response: {requestId: " << response.requestId << '}';
    return os;
}