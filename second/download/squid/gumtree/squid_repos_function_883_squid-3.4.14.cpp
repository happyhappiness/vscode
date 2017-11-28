static bool
limitError(int const anErrno)
{
    return anErrno == ENFILE || anErrno == EMFILE;
}