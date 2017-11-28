void
StoreSearchCoss::next(void (callback)(void *cbdata), void *cbdata)
{
    next();
    callback (cbdata);
}