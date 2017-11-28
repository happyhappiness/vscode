    }

    /* NOTREACHED */
    return 0;
}

#else /* !USE_ICMP */

#include <ostream>
int
main(int argc, char *argv[])
{
    std::cerr << argv[0] << ": ICMP support not compiled in." << std::endl;
    return 1;
}

#endif /* USE_ICMP */

