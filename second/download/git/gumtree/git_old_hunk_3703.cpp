		}
		free_worktrees(worktrees);
	}
	return 0;
}

int cmd_worktree(int ac, const char **av, const char *prefix)
{
	struct option options[] = {
		OPT_END()
	};

	if (ac < 2)
		usage_with_options(worktree_usage, options);
	if (!strcmp(av[1], "add"))
		return add(ac - 1, av + 1, prefix);
	if (!strcmp(av[1], "prune"))
		return prune(ac - 1, av + 1, prefix);
	if (!strcmp(av[1], "list"))
		return list(ac - 1, av + 1, prefix);
	usage_with_options(worktree_usage, options);
}
