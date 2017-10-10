			return;
		} else {
			die("could not read file '%s': %s", filename,
				strerror(errno));
		}
	} else {
		strbuf_getline(&str, fp, '\n');
		*read_bad = strbuf_detach(&str, NULL);
		strbuf_getline(&str, fp, '\n');
		*read_good = strbuf_detach(&str, NULL);
	}
	strbuf_release(&str);
	fclose(fp);
}

