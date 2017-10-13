error(_("%s: cannot parse parent commit %s"),
			command_to_string(command),
			oid_to_hex(&parent->object.oid));