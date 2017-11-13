die("Could not run 'git rev-list %s --not --remotes -n 1' command in submodule %s",
				sha1_to_hex(sha1), path);