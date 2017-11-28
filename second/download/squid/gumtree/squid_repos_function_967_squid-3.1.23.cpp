void
HttpMsg::_unlock()
{
    assert(lock_count > 0);
    --lock_count;

    if (0 == lock_count)
        delete this;
}