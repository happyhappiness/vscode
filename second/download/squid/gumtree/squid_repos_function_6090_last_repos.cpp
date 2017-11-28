FileOpeningConfig &
FileOpeningConfig::locked(unsigned int attempts)
{
    lockAttempts = attempts;
    // for simplicity, correct locking flags are preset in constructing methods
    return *this;
}