LONG CALLBACK WIN32_ExceptionHandler(EXCEPTION_POINTERS* ep)
{
    EXCEPTION_RECORD* er;

    er = ep->ExceptionRecord;

    switch (er->ExceptionCode) {

    case EXCEPTION_ACCESS_VIOLATION:
        raise(SIGSEGV);
        break;

    case EXCEPTION_DATATYPE_MISALIGNMENT:

    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:

    case EXCEPTION_IN_PAGE_ERROR:
        raise(SIGBUS);
        break;

    default:
        break;
    }

    return EXCEPTION_CONTINUE_SEARCH;
}