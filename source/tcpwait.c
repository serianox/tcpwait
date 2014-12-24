/*
 *	Copyright 2014 Thomas Duboucher <thomas at duboucher dot eu>
 *
 *	This software is governed by the CeCILL-B license under French law and
 *	abiding by the rules of distribution of free software.  You can  use,
 *	modify and/ or redistribute the software under the terms of the CeCILL-B
 *	license as circulated by CEA, CNRS and INRIA at the following URL
 *	"http://www.cecill.info".
 *
 *	As a counterpart to the access to the source code and  rights to copy,
 *	modify and redistribute granted by the license, users are provided only
 *	with a limited warranty  and the software's author,  the holder of the
 *	economic rights,  and the successive licensors  have only  limited
 *	liability.
 *
 *	In this respect, the user's attention is drawn to the risks associated
 *	with loading,  using,  modifying and/or developing or reproducing the
 *	software by the user in light of its specific status of free software,
 *	that may mean  that it is complicated to manipulate,  and  that  also
 *	therefore means  that it is reserved for developers  and  experienced
 *	professionals having in-depth computer knowledge. Users are therefore
 *	encouraged to load and test the software's suitability as regards their
 *	requirements in conditions enabling the security of their systems and/or
 *	data to be ensured and,  more generally, to use and operate it in the
 *	same conditions as regards security.
 *
 *	The fact that you are presently reading this means that you have had
 *	knowledge of the CeCILL-B license and that you accept its terms.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

#define AUSEC_XATTR_NAME "user.integrity.ausec"
#define AUSEC_DEFAULT_CONFIGURATION_FILE "/etc/ausec.cfg"
#define AUSEC_DEFAULT_ROOT_DIRECTORY NULL

static struct
{
	bool verbose;
}
configuration =
{
	.verbose = false,
};

#define log_debug(...) \
	((configuration.verbose)? fprintf(stderr, __VA_ARGS__): 0)

#define log_verbose(...) \
	((configuration.verbose)? fprintf(stderr, __VA_ARGS__): 0)

#define log_message(...) \
	(fprintf(stdout, __VA_ARGS__))

#define log_warning(...) \
	(fprintf(stderr, __VA_ARGS__))

#define log_error(...) \
	(fprintf(stderr, __VA_ARGS__))

void usage(const char * program)
{
	printf("\
Usage: %s [options]\n\
", program);
}

void parse_arguments(int argc, char * argv[])
{
	// http://www.ibm.com/developerworks/aix/library/au-unix-getopt.html
	const char * options = ":";

	const struct option long_options[] =
	{
		{"verbose", no_argument, NULL, 0},
		//{"version", no_argument, NULL, 'v'},
		{"help", no_argument, NULL, 'h'},
		{NULL, no_argument, NULL, 0}
	};

	int option, option_index; while ((option = getopt_long(argc, argv, options, long_options, &option_index)) != -1)
	{
		switch (option)
		{
			case 'h':
			case '?':
			case ':':
				usage(0[argv]);
				exit(EXIT_SUCCESS);
			case 0:
				if (strcmp("verbose", long_options[option_index].name) == 0)
					configuration.verbose = true;

				break;
		}
	}

	if ((argc - optind) > 0)
	{
		usage(0[argv]);
		exit(-1);
	}
}

int main(int argc, char * argv[])
{
	parse_arguments(argc, argv);
}
