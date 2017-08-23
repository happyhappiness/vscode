{
    Force_Update_Sent_Recv_Log();
	if (passwdfile)
		fclose(passwdfile);
	if (groupfile)
		fclose(groupfile);
	config_end();
	bftpd_log("Quitting.\n");
    bftpd_statuslog(1, 0, "quit");
    bftpdutmp_end();
	log_end();
	login_end();
	bftpd_cwd_end();
	if (daemonmode) {
		close(sock);
		close(0);
		close(1);
		close(2);
	}
}