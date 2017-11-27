static int mic_read_power(int mic)
{
	U32 ret;
	MicPwrUsage power_use;

	ret = MicGetPowerUsage(mic_handle,&power_use);
	if (ret != MIC_ACCESS_API_SUCCESS) {
		ERROR("mic plugin: Problem getting Power Usage: %s",
			MicGetErrorString(ret));
		return (1);
	}

	/* power is in uWatts, current in mA, voltage in uVolts..   convert to
	 * base unit */
	#define SUB_POWER(name) do { if (ignorelist_match(power_ignore,#name)==0) \
		mic_submit_power(mic,"power",#name,(gauge_t)power_use.name.prr*0.000001); \
	} while(0)
	#define SUB_VOLTS(name) do { if (ignorelist_match(power_ignore,#name)==0) {\
		mic_submit_power(mic,"power",#name,(gauge_t)(power_use.name.pwr*0.000001)); \
		mic_submit_power(mic,"current",#name,(gauge_t)(power_use.name.cur*0.001)); \
		mic_submit_power(mic,"voltage",#name,(gauge_t)(power_use.name.volt*0.000001)); \
	}} while(0)

	SUB_POWER(total0);
	SUB_POWER(total1);
	SUB_POWER(inst);
	SUB_POWER(imax);
	SUB_POWER(pcie);
	SUB_POWER(c2x3);
	SUB_POWER(c2x4);
	SUB_VOLTS(vccp);
	SUB_VOLTS(vddg);
	SUB_VOLTS(vddq);

	return (0);
}