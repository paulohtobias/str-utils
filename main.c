#include "str-utils.h"

#define t 5

//int main_argv(int argc, char *argv[]) {
int main(int argc, char *argv[]) {
	char *str = str_join(" ", argv, argc);

	for (int i = 0; i < argc; i++) {
		printf("%d: '%s'\n", i, argv[i]);
	}

	int c;
	char **a = str_to_argv(str, &c);
	if (a != NULL) {
		for (int i = 0; i < c; i++) {
			printf("%d: '%s'\n", i, a[i]);
		}
	}
	free(str);
	return 0;
}

int main_join(int argc, char *argv[]) {
	char *bla = str_join(", ", argv, argc);
	printf("%s\n", bla);
	free(bla);

	return 0;
}

int main_cp_ct(int argc, char *argv[]) {
//int main(int argc, char *argv[]) {

	char *a = "paulo ";
	char *src = "oi";
	char *dest = NULL;
	int n = 0;

	int m = 0;
	if (m == 0) {
		str_copy(&dest, a);
		n = (int) str_append(&dest, src);
	} else {
		dest = str_concat(a, src);
		if (dest) {
			n = strlen(dest) + 1;
		}
	}

	printf("%d: '%s'\n", n, dest);

	free(dest);

	return 0;
}

int main_regex(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "falta argumentos\n");
		return 1;
	}

	char *string = argv[1];
	char *regex_pattern = argv[2];

	/*regex_t regex;

	if (regcomp(&regex, regex_pattern, REG_EXTENDED | REG_ICASE) != 0) {
		fprintf(stderr, "error compiling\n");
		return 1;
	}
	printf("%d\n", regex.re_nsub);

	regmatch_t matches[regex.re_nsub * 3];
	if (regexec(&regex, string, regex.re_nsub * 3, matches, 0) != 0) {
		printf("No match\n");
		return 0;
	}

	for (int i = 0; i < regex.re_nsub * 3; i++) {
		printf("(%d, %d): %.*s\n", matches[i].rm_so, matches[i].rm_eo, matches[i].rm_eo - matches[i].rm_so, string + matches[i].rm_so);
	}

	regfree(&regex);*/

	return 0;
}

int main2(int argc, char *argv[]){
	printf("%d\n", str_ends_with(argv[1], argv[2]));
	return 0;
}
