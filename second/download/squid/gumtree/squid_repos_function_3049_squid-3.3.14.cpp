std::ostream &operator <<(std::ostream &os, const StoreEntry &e)
{
    return os << e.swap_filen << '@' << e.swap_dirn << '=' <<
           e.mem_status << '/' << e.ping_status << '/' << e.store_status << '/' <<
           e.swap_status;
}