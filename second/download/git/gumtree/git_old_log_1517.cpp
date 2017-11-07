die(Q_("pack has %d unresolved delta",
		       "pack has %d unresolved deltas",
		       nr_deltas - nr_resolved_deltas),
		    nr_deltas - nr_resolved_deltas);