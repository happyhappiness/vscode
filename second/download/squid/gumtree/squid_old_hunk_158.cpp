}

/// \ingroup ErrorPageInternal
#define CVT_BUF_SZ 512

const char *
ErrorState::Convert(char token, bool allowRecursion)
{
    static MemBuf mb;
    const char *p = NULL;	/* takes priority over mb if set */
    int do_quote = 1;
    char ntoabuf[MAX_IPSTRLEN];

    mb.reset();

    switch (token) {

    case 'a':

        if (request && request->auth_user_request)
            p = request->auth_user_request->username();

        if (!p)
            p = "-";

        break;

    case 'b':
        // NP: dynamic location of proxy-port not supported on 3.1
        // display the generic well-known port instead
        p = "3128";
        break;

    case 'B':
        p = request ? ftpUrlWith2f(request) : "[no URL]";

        break;

    case 'c':
        p = errorPageName(type);

        break;

    case 'D':
        if (!allowRecursion)
            p = "%D";  // if recursion is not allowed, do not convert
#if USE_SSL
