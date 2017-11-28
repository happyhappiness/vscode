static
    void
    handler( int signo ) {
        ::term_flag = signo;
        if ( getpid() == getpgrp() ) kill( -getpgrp(), signo );
        exit(1);
    }