static void end_align_handler(struct ref_formatting_stack *stack)
{
	struct align *align = (struct align *)stack->at_end_data;
	struct strbuf s = STRBUF_INIT;

	strbuf_utf8_align(&s, align->position, align->width, stack->output.buf);
	strbuf_swap(&stack->output, &s);
	strbuf_release(&s);
}