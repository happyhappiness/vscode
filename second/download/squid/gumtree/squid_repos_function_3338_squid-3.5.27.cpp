void
DelayId::delayRead(DeferredRead const &aRead)
{
    assert (compositeId != NULL);
    compositeId->delayRead(aRead);

}