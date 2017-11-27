static void apc_submit (struct apc_detail_s *apcups_detail)
{
	apc_submit_generic ("apcups_voltage",    "input",   apcups_detail->linev);
	apc_submit_generic ("apcups_voltage",    "output",  apcups_detail->outputv);
	apc_submit_generic ("apcups_voltage",    "battery", apcups_detail->battv);
	apc_submit_generic ("apcups_charge",     "",        apcups_detail->bcharge);
	apc_submit_generic ("apcups_charge_pct", "",        apcups_detail->loadpct);
	apc_submit_generic ("apcups_timeleft",   "",        apcups_detail->timeleft);
	apc_submit_generic ("apcups_temp",       "",        apcups_detail->itemp);
	apc_submit_generic ("apcups_frequency",  "input",   apcups_detail->linefreq);
}