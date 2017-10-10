	while (pos < active_nr) {
		ce = active_cache[pos++];
		stage = ce_stage(ce);
		if (strcmp(ce->name, it->string) || !stage)
			break;
		stages[stage - 1].mode = ce->ce_mode;
		hashcpy(stages[stage - 1].oid.hash, ce->oid.hash);
		sum |= (1 << (stage - 1));
	}
	if (sum != d->stagemask)
		die("BUG: observed stagemask 0x%x != expected stagemask 0x%x", sum, d->stagemask);

	if (s->null_termination)
