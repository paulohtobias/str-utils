#include "str-utils.h"

char *str_from_file(const char *file_name){
	char *str = NULL;
	FILE *in = fopen(file_name, "rb");
	if(in == NULL){
		return NULL;
	}

	fseek(in, 0, SEEK_END);
	int size = ftell(in) + 1;
	rewind(in);
	str = malloc(size);
	if(str == NULL){
		return NULL;
	}
	fread(str, 1, size, in);
	str[size - 1] = '\0';
	fclose(in);

	return str;
}

size_t str_copy(char **dest, const char *src) {
	free(*dest);
	*dest = NULL;

	if (src == NULL) {
		return 0;
	}

	size_t src_len = strlen(src) + 1;
	*dest = malloc(src_len);
	strcpy(*dest, src);

	return src_len;
}

size_t str_append(char **dest, const char *src) {
	size_t dest_len = 0;

	if (*dest != NULL) {
		dest_len = strlen(*dest);
	}

	if (src == NULL) {
		return dest_len;
	}

	size_t src_len = strlen(src);

	*dest = realloc(*dest, dest_len + src_len + 1);

	if (*dest == NULL) {
		perror("realloc");
		return 0;
	}

	size_t i;
	i = 0;
	while (1) {
		if (((*dest)[i + dest_len] = src[i]) == '\0') {
			break;
		}
		i++;
	}

	dest_len += src_len;

	return dest_len + 1;
}

char *str_concat(const char *dest, const char *src) {
	size_t dest_len = 0;
	char *new = NULL;

	if (dest != NULL) {
		dest_len = strlen(dest);
	} else {
		str_copy(&new, src);
		return new;
	}

	if (src == NULL) {
		new = malloc(dest_len + 1);
		strcpy(new, dest);

		return new;
	}

	size_t src_len = strlen(src);

	new = malloc(dest_len + src_len + 1);

	size_t i, j;
	i = j = 0;

	strcpy(new, dest);
	while (1) {
		if ((new[i + dest_len] = src[i]) == '\0') {
			break;
		}
		i++;
	}

	return new;
}

char *_str_join_list(const char *separator, void *list, size_t item_size, size_t list_len, char *(*to_str)(void *)) {
	char *str = NULL;
	char *item_str;
	void *item;

	size_t i;
	for (i = 0; i < list_len - 1; i++) {
		item = list + (i * item_size);
		item_str = item;
		if (to_str != NULL) {
			item_str = to_str(item);
		}

		str_append(&str, item_str);
		str_append(&str, separator);

		free(item_str);
	}
	item = list + (i * item_size);
	item_str = to_str(item);

	str_append(&str, item_str);

	free(item_str);

	return str;
}

char *str_join(const char *separator, char **list, size_t list_len) {
	char *str = NULL;

	size_t i;
	for (i = 0; i < list_len - 1; i++) {
		str_append(&str, list[i]);
		str_append(&str, separator);
	}
	str_append(&str, list[i]);

	return str;
}

char *str_replace(const char *orig, const char *rep, const char *with){
	char *result;		// the return string
	const char *ins;	// the next insert point
	char *tmp;			// varies
	int len_rep;		// length of rep (the string to remove)
	int len_with;		// length of with (the string to replace rep with)
	int len_front;		// distance between rep and end of last rep
	int count;			// number of replacements

	// sanity checks and initialization
	if (!orig && !rep)
		return NULL;
	len_rep = strlen(rep);
	if (len_rep == 0)
		return NULL; // empty rep causes infinite loop during count
	if (!with)
		with = "";
	len_with = strlen(with);

	// count the number of replacements needed
	ins = orig;
	for (count = 0; (tmp = strstr(ins, rep)) ; ++count) {
		ins = tmp + len_rep;
	}

	tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

	if (!result)
		return NULL;

	// first time through the loop, all the variable are set correctly
	// from here on,
	//    tmp points to the end of the result string
	//    ins points to the next occurrence of rep in orig
	//    orig points to the remainder of orig after "end of rep"
	while (count--) {
		ins = strstr(orig, rep);
		len_front = ins - orig;
		tmp = strncpy(tmp, orig, len_front) + len_front;
		tmp = strcpy(tmp, with) + len_with;
		orig += len_front + len_rep; // move to next "end of rep"
	}
	strcpy(tmp, orig);
	return result;
}

char *str_replace_char(char *str, int rep, int with) {
	size_t i;
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] == rep) {
			str[i] = with;
		}
	}

	return str;
}

int __strcmpn_atoi(const char *str, int *index){
	int i = 0;
	while(isdigit(str[i])){
		i++;
	}
	(*index) += i - 1;

	return atoi(str);
}

int strcmpn(const char *s1, const char *s2){
	//Getting the lengths of s1 and s2
	int l1 = strlen(s1);
	int l2 = strlen(s2);

	//Used to compare the chars.
	int c1, c2;

	//Variables to store the numbers inside the strings
	int n1 = 0, n2 = 0;

	int i1, i2;
	for(i1 = 0, i2 = 0; i1 < l1 && i2 < l2; i1++, i2++){
		if(isdigit(s1[i1]) && isdigit(s2[i2])){

			//Getting the number inside s1.
			n1 = __strcmpn_atoi(&s1[i1], &i1);

			//Getting the number inside s2.
			n2 = __strcmpn_atoi(&s2[i2], &i2);

			if(n1 != n2){
				return n1 - n2;
			}
		}else{
			c1 = tolower(s1[i1]);
			c2 = tolower(s2[i2]);
			if(c1 != c2){
				return c1 - c2;
			}
		}
	}

	//Testing if there are still text left in one string
	if( (i1 == l1) && (i2 < l2) )
		return -1;
	else if( (i1 < l1) && (i2 == l2) )
		return 1;
	return 0;
}

int str_ends_with(const char *str, const char *suffix){
	size_t len_str = strlen(str);
	size_t len_suffix = strlen(suffix);

	if(len_str < len_suffix){
		return 0;
	}

	int i;
	for(i = len_str - len_suffix; i < len_str; i++){
		if(str[i] != suffix[i - (len_str - len_suffix)]){
			return 0;
		}
	}

	return 1;
}

int str_match_regex(const char *str, const char *regex_pattern, const regex_t *regex) {
	regex_t _regex;

	// Need to recompile the pattern.
	int need_free = 0;
	if (regex == NULL) {
		need_free = 1;
		if (regcomp(&_regex, regex_pattern, REG_EXTENDED | REG_NOSUB | REG_ICASE) != 0) {
			return 0;
		}
	} else {
		memcpy(&_regex, regex, sizeof _regex);
	}

	int match_result = regexec(&_regex, str, 0, NULL, 0) == 0;

	if (need_free) {
		regfree(&_regex);
	}

	return match_result;
}

int str_exec_regex(const char *str, const char *regex_pattern) {
	return str_match_regex(str, regex_pattern, NULL);
}


char **str_to_argv(const char *_str, int *argc) {
	*argc = 0;

	// Removing leading whitespace.
	for (; isspace(*_str); _str++);

	// Cheking if the string is empty.
	if (*_str == '\0') {
		return NULL;
	}

	// Removing trailing whitespace.
	char *str = NULL;
	size_t str_len = str_copy(&str, _str) - 1;
	for (; isspace(str[str_len - 1]); str_len--);


	// We start with 1 argument and we call realloc whenever we find more.
	// Maybe we could count the number of spaces as an initial approximation
	// and do just one realloc at the end?
	*argc = 1;
	char **argv = calloc(*argc, sizeof(char *));

	// Automaton states and transitions.
	typedef int dfa_state_t;
	typedef enum dfa_transition_t {
		DT_SPACE = 0,
		DT_QUOTES = 1,
		DT_ALNUM = 2
	} dfa_transition_t;

	int dfa[3][3] = {
		{0, 3, 1},
		{0, 3, 1},
		{3, 1, 3}
	};
	dfa_state_t state = 0;
	dfa_transition_t symbol;

	int temp;
	int i, arg_len, argv_index = 0;
	for (i = 0; i < str_len; i++) {
		// Consuming leading whitespace.
		while (isspace(str[i])) {
			i++;
		}

		// Measuring the length of the argument.
		arg_len = 0;
		do {
			if (isspace(str[i + arg_len]) || str[i + arg_len] == '\0') {
				symbol = DT_SPACE;
			} else if (str[i + arg_len] == '\"') {
				symbol = DT_QUOTES;
			} else{
				symbol = DT_ALNUM;
			}

			state = dfa[state][symbol];
			arg_len++;
		} while (state != 0);

		if (arg_len > 0) {
			// Copying the argument
			if (argv_index >= *argc) {
				(*argc)++;
				argv = realloc(argv, *argc * sizeof(char *));
			}
			argv[argv_index] = malloc(arg_len--);
			temp = str[i + arg_len];
			str[i + arg_len] = '\0';
			strcpy(argv[argv_index], str + i);
			argv_index++;
			str[i + arg_len] = temp;
		}

		i += arg_len;
	}

	return argv;
}
