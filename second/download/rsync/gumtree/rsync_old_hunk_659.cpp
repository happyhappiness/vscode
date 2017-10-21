static struct sum_struct *receive_sums(int f)
{
	struct sum_struct *s;
	int i;
	OFF_T offset = 0;

	s = (struct sum_struct *)malloc(sizeof(*s));
	if (!s) out_of_memory("receive_sums");

	s->count = read_int(f);
	s->n = read_int(f);
	s->remainder = read_int(f);  
	s->sums = NULL;
