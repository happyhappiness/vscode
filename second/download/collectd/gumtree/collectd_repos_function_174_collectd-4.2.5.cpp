static void apc_submit (struct apc_detail_s *apcups_detail)
{
	apc_submit_generic ("voltage",    "input",   apcups_detail->linev);
	apc_submit_generic ("voltage",    "output",  apcups_detail->outputv);
	apc_submit_generic ("voltage",    "battery", apcups_detail->battv);
	apc_submit_generic ("charge",     "",        apcups_detail->bcharge);
	apc_submit_generic ("percent",    "load",    apcups_detail->loadpct);
	apc_submit_generic ("timeleft",   "",        apcups_detail->timeleft);
	apc_submit_generic ("temperature", "",       apcups_detail->itemp);
	apc_submit_generic ("frequency",  "input",   apcups_detail->linefreq);
}