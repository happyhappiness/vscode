static void advise_checkout_pull_push(void)
{
	if (!advice_push_non_ff_matching || !advice_push_update_rejected)
		return;
	advise(_(message_advice_checkout_pull_push));
}