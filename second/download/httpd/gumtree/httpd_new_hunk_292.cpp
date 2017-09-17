/*
 *  Abstraction layer for loading
 *  Apache modules under run-time via 
 *  dynamic shared object (DSO) mechanism
 */

#ifdef RHAPSODY
#include <mach-o/dyld.h>
#include "httpd.h"
#include "http_log.h"

ap_private_extern
void undefined_symbol_handler(const char *symbolName)
{
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_EMERG, NULL,
                 "dyld found undefined symbol: %s\n"
                 "Aborting.\n",
                 symbolName);
    abort();
}

ap_private_extern
NSModule multiple_symbol_handler (NSSymbol s, NSModule old, NSModule new)
{
    /*
     * Since we can't unload symbols, we're going to run into this
     * every time we reload a module. Workaround here is to just
     * rebind to the new symbol, and forget about the old one.
     * This is crummy, because it's basically a memory leak.
     * (See Radar 2262020 against dyld).
     */

#ifdef DEBUG
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_DEBUG, NULL,
                 "dyld found a multiply defined symbol %s in modules:\n"
                 "%s\n%s\n",
                 NSNameOfSymbol(s),
                 NSNameOfModule(old), NSNameOfModule(new));
#endif

    return(new);
}

ap_private_extern
void linkEdit_symbol_handler (NSLinkEditErrors c, int errorNumber,
                              const char *fileName, const char *errorString)
{
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_EMERG, NULL,
                 "dyld errors during link edit for file %s\n%s\n",
                 fileName, errorString);
    abort();
}

#endif /*RHAPSODY*/

void ap_os_dso_init(void)
{
#if defined(RHAPSODY)
    NSLinkEditErrorHandlers handlers;

    handlers.undefined = undefined_symbol_handler;
    handlers.multiple  = multiple_symbol_handler;
    handlers.linkEdit  = linkEdit_symbol_handler;

    NSInstallLinkEditErrorHandlers(&handlers);
#endif
}

void *ap_os_dso_load(const char *path)
{
#if defined(HPUX) || defined(HPUX10)
    shl_t handle;
    handle = shl_load(path, BIND_IMMEDIATE|BIND_VERBOSE|BIND_NOSTART, 0L);
    return (void *)handle;

#elif defined(RHAPSODY)
    NSObjectFileImage image;
    if (NSCreateObjectFileImageFromFile(path, &image) !=
        NSObjectFileImageSuccess)
        return NULL;
    return NSLinkModule(image, path, TRUE);

#elif defined(OSF1) ||\
    (defined(__FreeBSD_version) && (__FreeBSD_version >= 220000))
    return dlopen((char *)path, RTLD_NOW | RTLD_GLOBAL);

#else
    return dlopen(path, RTLD_NOW | RTLD_GLOBAL);
#endif
}

void ap_os_dso_unload(void *handle)
{
#if defined(HPUX) || defined(HPUX10)
    shl_unload((shl_t)handle);

#elif defined(RHAPSODY)
    NSUnLinkModule(handle,FALSE);

#else
    dlclose(handle);
#endif

    return;
}

void *ap_os_dso_sym(void *handle, const char *symname)
{
#if defined(HPUX) || defined(HPUX10)
