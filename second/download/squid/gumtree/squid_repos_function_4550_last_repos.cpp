void
Store::LocalSearch::next(void (aCallback)(void *), void *aCallbackData)
{
    next();
    aCallback (aCallbackData);
}