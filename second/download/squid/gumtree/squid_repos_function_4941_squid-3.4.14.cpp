bool
Rock::Rebuild::doneAll() const
{
    return dbOffset >= dbSize && AsyncJob::doneAll();
}