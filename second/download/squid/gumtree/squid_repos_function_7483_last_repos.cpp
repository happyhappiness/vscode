std::ostream &
Security::operator <<(std::ostream &os, const Security::EncryptorAnswer &answer)
{
    return os << answer.conn << ", " << answer.error;
}