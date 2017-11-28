bool
HttpReply::olderThan(const HttpReply *them) const
{
    if (!them || !them->date || !date)
        return false;
    return date < them->date;
}