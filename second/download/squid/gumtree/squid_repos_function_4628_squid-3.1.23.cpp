bool
StoreSearchCoss::next()
{
    current = next_;

    if (next_)
        next_ = next_->prev;

    if (!current)
        _done = true;

    return current != NULL;
}