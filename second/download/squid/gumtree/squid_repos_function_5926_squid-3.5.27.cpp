void
AsyncCall::print(std::ostream &os)
{
    os << name;
    if (const CallDialer *dialer = getDialer())
        dialer->print(os);
    else
        os << "(?" << this << "?)";
}