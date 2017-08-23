void handler_sigalrm(int signum)
{
    /* Log user out. -- Jesse <slicer69@hotmail.com> */
    bftpdutmp_end();
    // Force_Update_Sent_Recv_Log();

    if (alarm_type) {
        close(alarm_type);
        bftpd_log("Kicked from the server due to data connection timeout.\n");
        control_printf(SL_FAILURE, "421 Kicked from the server due to data connection timeout.");
        exit(0);
    } else {
        bftpd_log("Kicked from the server due to control connection timeout.\n");
        control_printf(SL_FAILURE, "421 Kicked from the server due to control connection timeout.");
        exit(0);
    }
}