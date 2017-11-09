static void advise_ref_already_exists(void)
{
	if (!advice_push_already_exists || !advice_push_update_rejected)
		return;
	advise(_(message_advice_ref_already_exists));
}