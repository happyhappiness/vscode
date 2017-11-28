int
main(int, char *[])
{
    std::string sbuf;
    close(2);
    if (open(_PATH_DEVNULL, O_RDWR) < 0) {
        ; // the irony of having to close(2) earlier is that we cannot report this failure.
    }
    while (getline(std::cin, sbuf)) {
        // tailing newline is removed by getline
        const int rv = remove(sbuf.c_str());
        if (rv < 0)
            std::cout << "ERR" << std::endl; // endl flushes
        else
            std::cout << "OK" << std::endl;
    }

    return 0;
}