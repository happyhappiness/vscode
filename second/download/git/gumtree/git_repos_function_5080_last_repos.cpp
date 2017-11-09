static void advise_pull_before_push(void)
{
	if (!advice_push_non_ff_current || !advice_push_update_rejected)
		return;
	advise(_(message_advice_pull_before_push));
}