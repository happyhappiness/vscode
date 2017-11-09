static enum contains_result contains_tag_algo(struct commit *candidate,
					      const struct commit_list *want,
					      struct contains_cache *cache)
{
	struct contains_stack contains_stack = { 0, 0, NULL };
	enum contains_result result = contains_test(candidate, want, cache);

	if (result != CONTAINS_UNKNOWN)
		return result;

	push_to_contains_stack(candidate, &contains_stack);
	while (contains_stack.nr) {
		struct contains_stack_entry *entry = &contains_stack.contains_stack[contains_stack.nr - 1];
		struct commit *commit = entry->commit;
		struct commit_list *parents = entry->parents;

		if (!parents) {
			*contains_cache_at(cache, commit) = CONTAINS_NO;
			contains_stack.nr--;
		}
		/*
		 * If we just popped the stack, parents->item has been marked,
		 * therefore contains_test will return a meaningful yes/no.
		 */
		else switch (contains_test(parents->item, want, cache)) {
		case CONTAINS_YES:
			*contains_cache_at(cache, commit) = CONTAINS_YES;
			contains_stack.nr--;
			break;
		case CONTAINS_NO:
			entry->parents = parents->next;
			break;
		case CONTAINS_UNKNOWN:
			push_to_contains_stack(parents->item, &contains_stack);
			break;
		}
	}
	free(contains_stack.contains_stack);
	return contains_test(candidate, want, cache);
}