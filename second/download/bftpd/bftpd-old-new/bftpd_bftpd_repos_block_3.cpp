{
   bftpd_log("Caught HUP signal. Re-reading config file.\n");
   Reread_Config_File();
   signal(sig, handler_sighup);
}