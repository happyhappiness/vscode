YesNoNone::operator void*() const
{
    assert(option != 0); // must call configure() first
    return option > 0 ? (void*)this : NULL;
}