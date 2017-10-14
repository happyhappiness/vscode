static void show_compile_settings(void)
{
    printf("Server version: %s\n", ap_get_server_description());
    printf("Server built:   %s\n", ap_get_server_built());
    printf("Server's Module Magic Number: %u:%u\n",
           MODULE_MAGIC_NUMBER_MAJOR, MODULE_MAGIC_NUMBER_MINOR);
#if APR_MAJOR_VERSION >= 2
    printf("Server loaded:  APR %s\n", apr_version_string());
    printf("Compiled using: APR %s\n", APR_VERSION_STRING);
#else
    printf("Server loaded:  APR %s, APR-UTIL %s\n",
           apr_version_string(), apu_version_string());
    printf("Compiled using: APR %s, APR-UTIL %s\n",
           APR_VERSION_STRING, APU_VERSION_STRING);
#endif
    /* sizeof(foo) is long on some platforms so we might as well
     * make it long everywhere to keep the printf format
     * consistent
     */
    printf("Architecture:   %ld-bit\n", 8 * (long)sizeof(void *));

    show_mpm_settings();

    printf("Server compiled with....\n");
#ifdef BIG_SECURITY_HOLE
    printf(" -D BIG_SECURITY_HOLE\n");
#endif

#ifdef SECURITY_HOLE_PASS_AUTHORIZATION
    printf(" -D SECURITY_HOLE_PASS_AUTHORIZATION\n");
#endif

#ifdef OS
    printf(" -D OS=\"" OS "\"\n");
#endif

#ifdef HAVE_SHMGET
    printf(" -D HAVE_SHMGET\n");
#endif

#if APR_FILE_BASED_SHM
    printf(" -D APR_FILE_BASED_SHM\n");
#endif

#if APR_HAS_SENDFILE
    printf(" -D APR_HAS_SENDFILE\n");
#endif

#if APR_HAS_MMAP
    printf(" -D APR_HAS_MMAP\n");
#endif

#ifdef NO_WRITEV
    printf(" -D NO_WRITEV\n");
#endif

#ifdef NO_LINGCLOSE
    printf(" -D NO_LINGCLOSE\n");
#endif

#if APR_HAVE_IPV6
    printf(" -D APR_HAVE_IPV6 (IPv4-mapped addresses ");
#ifdef AP_ENABLE_V4_MAPPED
    printf("enabled)\n");
#else
    printf("disabled)\n");
#endif
#endif

#if APR_USE_FLOCK_SERIALIZE
    printf(" -D APR_USE_FLOCK_SERIALIZE\n");
#endif

#if APR_USE_SYSVSEM_SERIALIZE
    printf(" -D APR_USE_SYSVSEM_SERIALIZE\n");
#endif

#if APR_USE_POSIXSEM_SERIALIZE
    printf(" -D APR_USE_POSIXSEM_SERIALIZE\n");
#endif

#if APR_USE_FCNTL_SERIALIZE
    printf(" -D APR_USE_FCNTL_SERIALIZE\n");
#endif

#if APR_USE_PROC_PTHREAD_SERIALIZE
    printf(" -D APR_USE_PROC_PTHREAD_SERIALIZE\n");
#endif

#if APR_USE_PTHREAD_SERIALIZE
    printf(" -D APR_USE_PTHREAD_SERIALIZE\n");
#endif

#if APR_PROCESS_LOCK_IS_GLOBAL
    printf(" -D APR_PROCESS_LOCK_IS_GLOBAL\n");
#endif

#ifdef SINGLE_LISTEN_UNSERIALIZED_ACCEPT
    printf(" -D SINGLE_LISTEN_UNSERIALIZED_ACCEPT\n");
#endif

#if APR_HAS_OTHER_CHILD
    printf(" -D APR_HAS_OTHER_CHILD\n");
#endif

#ifdef AP_HAVE_RELIABLE_PIPED_LOGS
    printf(" -D AP_HAVE_RELIABLE_PIPED_LOGS\n");
#endif

#ifdef BUFFERED_LOGS
    printf(" -D BUFFERED_LOGS\n");
#ifdef PIPE_BUF
    printf(" -D PIPE_BUF=%ld\n",(long)PIPE_BUF);
#endif
#endif

    printf(" -D DYNAMIC_MODULE_LIMIT=%ld\n",(long)DYNAMIC_MODULE_LIMIT);

#if APR_CHARSET_EBCDIC
    printf(" -D APR_CHARSET_EBCDIC\n");
#endif

#ifdef NEED_HASHBANG_EMUL
    printf(" -D NEED_HASHBANG_EMUL\n");
#endif

/* This list displays the compiled in default paths: */
#ifdef HTTPD_ROOT
    printf(" -D HTTPD_ROOT=\"" HTTPD_ROOT "\"\n");
#endif

#ifdef SUEXEC_BIN
    printf(" -D SUEXEC_BIN=\"" SUEXEC_BIN "\"\n");
#endif

#ifdef DEFAULT_PIDLOG
    printf(" -D DEFAULT_PIDLOG=\"" DEFAULT_PIDLOG "\"\n");
#endif

#ifdef DEFAULT_SCOREBOARD
    printf(" -D DEFAULT_SCOREBOARD=\"" DEFAULT_SCOREBOARD "\"\n");
#endif

#ifdef DEFAULT_ERRORLOG
    printf(" -D DEFAULT_ERRORLOG=\"" DEFAULT_ERRORLOG "\"\n");
#endif

#ifdef AP_TYPES_CONFIG_FILE
    printf(" -D AP_TYPES_CONFIG_FILE=\"" AP_TYPES_CONFIG_FILE "\"\n");
#endif

#ifdef SERVER_CONFIG_FILE
    printf(" -D SERVER_CONFIG_FILE=\"" SERVER_CONFIG_FILE "\"\n");
#endif
}