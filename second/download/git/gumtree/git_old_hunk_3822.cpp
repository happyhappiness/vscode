			 submodule->update_strategy.type != SM_UPDATE_UNSPECIFIED)
			warn_multiple_config(me->commit_sha1, submodule->name,
					     "update");
		else if (parse_submodule_update_strategy(value,
			 &submodule->update_strategy) < 0)
				die(_("invalid value for %s"), var);
	}

	strbuf_release(&name);
	strbuf_release(&item);

	return ret;
