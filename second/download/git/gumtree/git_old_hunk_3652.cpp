			i--;
			break;
		}
		case OBJ_TREE:
			if (rev.shown_one)
				putchar('\n');
			printf("%stree %s%s\n\n",
					diff_get_color_opt(&rev.diffopt, DIFF_COMMIT),
					name,
					diff_get_color_opt(&rev.diffopt, DIFF_RESET));
			read_tree_recursive((struct tree *)o, "", 0, 0, &match_all,
					show_tree_object, NULL);
			rev.shown_one = 1;
			break;
		case OBJ_COMMIT:
			rev.pending.nr = rev.pending.alloc = 0;
			rev.pending.objects = NULL;
			add_object_array(o, name, &rev.pending);
