bool
AsyncCall::canFire()
{
    return !isCanceled;
}