static int files_reflog_iterator_peel(struct ref_iterator *ref_iterator,
				   struct object_id *peeled)
{
	die("BUG: ref_iterator_peel() called for reflog_iterator");
}