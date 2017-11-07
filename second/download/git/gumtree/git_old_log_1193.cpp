printf("[%s%s ",
		starts_with(head, "refs/heads/") ?
			head + 11 :
			!strcmp(head, "HEAD") ?
				_("detached HEAD") :
				head,
		initial_commit ? _(" (root-commit)") : "");