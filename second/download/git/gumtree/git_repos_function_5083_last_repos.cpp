static void advise_ref_fetch_first(void)
{
	if (!advice_push_fetch_first || !advice_push_update_rejected)
		return;
	advise(_(message_advice_ref_fetch_first));
}