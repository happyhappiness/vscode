void
Debug::Finish()
{
    // TODO: Optimize to remove at least one extra copy.
    _db_print("%s\n", Current->buf.str().c_str());

    Context *past = Current;
    Current = past->upper;
    if (Current)
        delete past;
    // else it was a static topContext from Debug::Start()
}