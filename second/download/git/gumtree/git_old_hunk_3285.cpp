				int saved;
				/*
				 * At this point we haven't read any configuration,
				 * and we know shared_repository should always be 0;
				 * but just in case we play safe.
				 */
				saved = shared_repository;
				shared_repository = 0;
				switch (safe_create_leading_directories_const(argv[0])) {
				case SCLD_OK:
				case SCLD_PERMS:
					break;
				case SCLD_EXISTS:
					errno = EEXIST;
					/* fallthru */
				default:
					die_errno(_("cannot mkdir %s"), argv[0]);
					break;
				}
				shared_repository = saved;
				if (mkdir(argv[0], 0777) < 0)
					die_errno(_("cannot mkdir %s"), argv[0]);
				mkdir_tried = 1;
				goto retry;
			}
			die_errno(_("cannot chdir to %s"), argv[0]);
