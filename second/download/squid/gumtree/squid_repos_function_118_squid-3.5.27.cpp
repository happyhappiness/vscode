void
Debug::Finish()
{
    if (Current) {
        _db_print("%s\n", Current->buf.str().c_str());
        delete Current;
        Current = NULL;
    }
}