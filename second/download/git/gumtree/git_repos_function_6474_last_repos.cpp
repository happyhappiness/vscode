static int empty_ref_iterator_peel(struct ref_iterator *ref_iterator,
				   struct object_id *peeled)
{
	die("BUG: peel called for empty iterator");
}