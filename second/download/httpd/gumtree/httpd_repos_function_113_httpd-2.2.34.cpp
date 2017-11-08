static apr_status_t seed_rand(void)
{
    int seed = 0;
    apr_status_t rv;
    rv = apr_generate_random_bytes((unsigned char*) &seed, sizeof(seed));
    if (rv) {
        apr_file_printf(errfile, "Unable to generate random bytes: %pm" NL, &rv);
        return rv;
    }
    srand(seed);
    return rv;
}