			goto out;
		}
	}
	fclose(config_file);
unlock_and_out:
	if (commit_lock_file(lock) < 0)
		ret = error("could not write config file %s: %s",
			    config_filename, strerror(errno));
out:
	free(filename_buf);
	return ret;
}

int git_config_rename_section(const char *old_name, const char *new_name)
