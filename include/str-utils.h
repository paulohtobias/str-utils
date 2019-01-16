/**
 * Paulo Tobias
 * paulohtobias@outlook.com
 */

#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

/**
 * Read all content from <code>file_name</code> into a string.
 *
 * @param file_name name of the file
 * @return a pointer to the new string
 */
char *str_from_file(const char *file_name);

/**
 * TODO: in copy, append and concat, size will be an in/out parameter
 * in order to skip the strlen cals. Write the documentation!!
 *
 * copy and append will now return *dest;
 *
 * then, optmize str_join to use these changes.
 */

/**
 * Copy a string.
 */
size_t str_copy(char **dest, const char *src);

size_t str_append(char **dest, const char *src);

char *str_concat(const char *dest, const char *src);


int str_qsort_ccmp(const void *s1, const void *s2);

int str_qsort_ccmp_null(const void *s1, const void *s2);


#define str_join_list(separator, list, list_len, type, to_str) \
	_str_join_list(separator, list, sizeof(type), list_len, (char *(*)(void *)) to_str)

char *_str_join_list(const char *separator, void *list, size_t item_size, size_t list_len, char *(*to_str)(void *));

char *str_join(const char *separator, const char **list, size_t list_len);


/**
 * Replace all ocurrences of <code>rep</code> in <code>orig</code> to
 * <code>with</code>.
 * <br>
 * Code taken from http://stackoverflow.com/questions/779875/what-is-the-function-to-replace-string-in-c/779960#779960
 *
 * @param orig a pointer to a string
 * @param rep the pattern that will be replaced
 * @param with the string that will replace <code>rep</code>
 * @return a pointer to a new string with all the changes
 */
char *str_replace(const char *orig, const char *rep, const char *with);

char *str_replace_char(char *str, int rep, int with);


/**
 * Compare 2 strings (case insensitive) and check for numbers in them.
 * <br><br>
 * In a normal call to strcmp, "foo10" < "foo2" because 1 < 2, even though 1 is
 * part of the number 10, which is greater than 2. So this function will compare
 * 10 with 2 and will return that "foo10" > "foo2".
 *
 * @param s1 first string
 * @param s2 second string
 * @return an integer less than, equal to, or greater than zero if s1
 * is found, respectively, to be less than, to match, or be greater than s2
 */
int strcmpn(const char *s1, const char *s2);

int str_starts_with(const char *str, const char *preffix);

/**
 * Check if <code>str</code> ends with <code>suffix</code>.
 *
 * @param str the string that will be checked
 * @param suffix the suffix
 * @return 1 if true and 0 if false
 */
int str_ends_with(const char *str, const char *suffix);

int str_exec_regex(const char *str, const char *regex_pattern);


/**
 * Creates an argv-like array of strings by parsing str.
 * The array size is stored into *argc.
 *
 * In case of an error, *argc will be set to 0 and the
 * function will return NULL.
 */
char **str_to_argv(const char *str, int *argc);

#endif /* STR_UTILS_H */
