
    printf("Compiled in modules:\n");
    for (n = 0; ap_loaded_modules[n]; ++n)
        printf("  %s\n", ap_loaded_modules[n]->name);
}

AP_DECLARE(const char *) ap_show_mpm(void)
{
    return MPM_NAME;
}
