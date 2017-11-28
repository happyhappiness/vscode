std::ostream &
operator <<(std::ostream &os, const Acl::Option &option)
{
    if (option.valued()) {
        os << '=';
        option.print(os);
    }
    return os;
}