std::ostream &Ipc::Mem::operator <<(std::ostream &os, const PageId &page)
{
    return os << "sh_page" << page.pool << '.' << page.number;
}