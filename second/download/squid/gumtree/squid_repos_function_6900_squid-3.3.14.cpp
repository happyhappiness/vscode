void
psignal( int sig, const char* msg )
{
    if ( msg && *msg ) fprintf( stderr, "%s: ", msg );
    if ( sig > 0 && sig < _sys_nsig )
        fprintf( stderr, "%s\n", _sys_siglist[sig] );
    else
        fputs( "(unknown)\n", stderr );
}