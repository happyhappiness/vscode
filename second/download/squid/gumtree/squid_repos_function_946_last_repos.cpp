void
DelayPool::createPool(u_char delay_class)
{
    if (pool)
        freeData();

    pool = CommonPool::Factory(delay_class, theComposite_);
}