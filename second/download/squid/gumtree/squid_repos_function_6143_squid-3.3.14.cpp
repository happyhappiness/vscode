bool
ESIInclude::dataNeeded() const
{
    return !(flags.finished || flags.failed);
}