				/*
				 * This sline was here to hang the
				 * lost lines in front of it.
				 */
				if (!context)
					continue;
				fputs(c_plain, stdout);
			}
			else
				fputs(c_new, stdout);
			for (j = 0; j < num_parent; j++) {
				if (p_mask & sl->flag)
					putchar('+');
