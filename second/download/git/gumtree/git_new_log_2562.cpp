die(include_depth_advice, MAX_INCLUDE_DEPTH, path,
			    !cf ? "<unknown>" :
			    cf->name ? cf->name :
			    "the command line");