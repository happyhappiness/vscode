HttpMsg *
HttpMsg::_lock()
{
    lock_count++;
    return this;
}