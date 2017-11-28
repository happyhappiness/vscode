void
esiTry::notifyParent()
{
    if (flags.attemptfailed) {
        if (flags.exceptok) {
            parent->provideData (exceptbuffer, this);
            exceptbuffer = NULL;
        } else if (flags.exceptfailed || except.getRaw() == NULL) {
            parent->fail (this, "esi:try - except claused failed, or no except clause found");
        }
    }

    /* nothing to do when except fails and attempt hasn't */
}