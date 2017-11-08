static void advise_ref_needs_force(void)
{
	if (!advice_push_needs_force || !advice_push_update_rejected)
		return;
	advise(_(message_advice_ref_needs_force));
}