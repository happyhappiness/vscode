const char *
make_challenge(char *domain, char *domain_controller)
{
    /* trying to circumvent some strange problem wih pointers in SMBLib */
    /* Ugly as hell, but the lib is going to be dropped... */
    strcpy(my_domain,domain);
    strcpy(my_domain_controller,domain_controller);
    if (init_challenge(my_domain, my_domain_controller) > 0) {
        return NULL;
    }
    return ntlm_make_challenge(my_domain, my_domain_controller, (char *)challenge, NONCE_LEN);
}