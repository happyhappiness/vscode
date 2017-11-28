int
SMB_Term()
{

#ifdef SMBLIB_INSTRUMENT

    SMBlib_Instrument_Term();	/* Clean up and print results */

#endif

    return 0;

}