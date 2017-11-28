bool
IdleConnList::removeAt(int index)
{
    if (index < 0 || index >= size_)
        return false;

    // shuffle the remaining entries to fill the new gap.
    for (; index < size_ - 1; ++index)
        theList_[index] = theList_[index + 1];
    theList_[--size_] = NULL;

    if (parent_) {
        parent_->noteConnectionRemoved();
        if (size_ == 0) {
            debugs(48, 3, "deleting " << hashKeyStr(this));
            delete this;
        }
    }

    return true;
}