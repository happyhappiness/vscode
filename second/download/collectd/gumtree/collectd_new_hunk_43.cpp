			remove(filename);
			return (-1);
		}

		/* The `%.*s' is needed because there is no null-byte behind
		 * the name. */
		fprintf(log, ",%.*s", (int) (tmp - name), name);
	}
	fprintf(log, "\n");
	fclose(log);

	return 0;
}
