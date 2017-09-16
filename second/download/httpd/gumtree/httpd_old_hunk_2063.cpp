/*

 *  Abstraction layer for loading

 *  Apache modules under run-time via 

 *  dynamic shared object (DSO) mechanism

 */



void *ap_os_dso_load(const char *path)

{

#if defined(HPUX) || defined(HPUX10)

    shl_t handle;

    handle = shl_load(path, BIND_IMMEDIATE|BIND_VERBOSE|BIND_NOSTART, 0L);

    return (void *)handle;

#else

#if defined(OSF1) ||\

    (defined(__FreeBSD_version) && (__FreeBSD_version >= 220000))

    return dlopen((char *)path, RTLD_NOW | RTLD_GLOBAL);

#else

    return dlopen(path, RTLD_NOW | RTLD_GLOBAL);

#endif

#endif

}



void ap_os_dso_unload(void *handle) 

{

#if defined(HPUX) || defined(HPUX10)

    shl_unload((shl_t)handle);

#else

    dlclose(handle);

#endif

    return;

}



void *ap_os_dso_sym(void *handle, const char *symname)

{

#if defined(HPUX) || defined(HPUX10)

