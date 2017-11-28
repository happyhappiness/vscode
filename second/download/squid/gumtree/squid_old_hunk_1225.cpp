void
Debug::Finish()
{
    if (Current) {
        _db_print("%s\n", Current->buf.str().c_str());
        delete Current;
        Current = NULL;
    }
}

std::ostream &
Raw::print(std::ostream &os) const
{
