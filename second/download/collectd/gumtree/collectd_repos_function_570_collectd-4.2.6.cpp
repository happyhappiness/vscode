static double ntpd_read_fp (int32_t val_int)
{
	double val_double;

	val_int = ntohl (val_int);
	val_double = ((double) val_int) / FP_FRAC;

	return (val_double);
}