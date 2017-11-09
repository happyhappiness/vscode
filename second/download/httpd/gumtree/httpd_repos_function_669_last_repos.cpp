static void init_dh_params(void)
{
    unsigned n;

    for (n = 0; n < sizeof(dhparams)/sizeof(dhparams[0]); n++)
        dhparams[n].dh = make_dh_params(dhparams[n].prime);
}