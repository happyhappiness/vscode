bool
Rock::HeaderUpdater::doneAll() const
{
    return !reader && !writer && AsyncJob::doneAll();
}