static int in_domain(const char *domain, const char *what)
{
    int dl = strlen(domain);
    int wl = strlen(what);

    if ((wl - dl) >= 0) {
        if (strcasecmp(domain, &what[wl - dl]) != 0) {
            return 0;
        }

        /* Make sure we matched an *entire* subdomain --- if the user
         * said 'allow from good.com', we don't want people from nogood.com
         * to be able to get in.
         */

        if (wl == dl) {
            return 1;                /* matched whole thing */
        }
        else {
            return (domain[0] == '.' || what[wl - dl - 1] == '.');
        }
    }
    else {
        return 0;
    }
}