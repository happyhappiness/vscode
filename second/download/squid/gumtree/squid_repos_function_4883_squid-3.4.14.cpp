char const *
CossSwapDir::stripePath() const
{
    if (!stripe_path) {
        String result = path;
        result.append("/stripe");
        const_cast<CossSwapDir *>(this)->stripe_path = xstrdup(result.termedBuf());
    }

    return stripe_path;
}