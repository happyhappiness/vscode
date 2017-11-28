bool
ConnStateData::isOpen() const
{
    return cbdataReferenceValid(this) && // XXX: checking "this" in a method
           fd >= 0 &&
           !fd_table[fd].closing();
}