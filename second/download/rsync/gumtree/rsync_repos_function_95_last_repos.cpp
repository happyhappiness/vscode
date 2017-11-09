const filter_rule *rule_template(uint32 rflags)
{
	static filter_rule template; /* zero-initialized */
	template.rflags = rflags;
	return &template;
}