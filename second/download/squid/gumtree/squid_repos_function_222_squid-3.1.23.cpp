int
SMB_Init()
{

    SMBlib_State = SMB_State_Started;

    signal(SIGPIPE, SIG_IGN);	/* Ignore these ... */

    /* If SMBLIB_Instrument is defines, turn on the instrumentation stuff */
#ifdef SMBLIB_INSTRUMENT

    SMBlib_Instrument_Init();

#endif

    return 0;

}