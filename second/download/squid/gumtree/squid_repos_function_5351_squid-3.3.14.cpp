void Throw(const char *message, const char *fileName, int lineNo, unsigned int id)
{

    // or should we let the exception recepient print the exception instead?

    if (fileName) {
        debugs(0, 3, fileName << ':' << lineNo << ": exception" <<
               (message ? ": " : ".") << (message ? message : ""));
    } else {
        debugs(0, 3, "exception" <<
               (message ? ": " : ".") << (message ? message : ""));
    }

    throw TextException(message, fileName, lineNo, id);
}