void
xfreeaddrinfo (struct addrinfo *ai)
{
    struct addrinfo *next;

    while (ai != NULL) {
        next = ai->ai_next;
        if (ai->ai_canonname != NULL)
            free (ai->ai_canonname);
        if (ai->ai_addr != NULL)
            free (ai->ai_addr);
        free (ai);
        ai = next;
    }
}