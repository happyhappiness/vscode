			for (j = 1; j < argc; j++)
				if (!strcmp(r->list[i].name, argv[j]))
					break;
			if (j == argc)
				continue;
		}
		printf("%s %s\n", oid_to_hex(&r->list[i].oid),
				r->list[i].name);
	}
	return 0;
}

/* Remember to update object flag allocation in object.h */
