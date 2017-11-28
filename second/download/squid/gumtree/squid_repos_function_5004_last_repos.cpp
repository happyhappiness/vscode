bool
Rock::Rebuild::doneAll() const
{
    return doneLoading() && doneValidating() && AsyncJob::doneAll();
}