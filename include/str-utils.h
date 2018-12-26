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

/**
 * Read all content from <code>file_name</code> into a string.
 *
 * @param file_name name of the file
 * @return a pointer to the new string
 */
char *str_from_file(const char *file_name);

/**
 * Copy a string.
 */
size_t str_copy(char **dest, const char *src);

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

/**
 * Check if <code>str</code> ends with <code>suffix</code>.
 *
 * @param str the string that will be checked
 * @param suffix the suffix
 * @return 1 if true and 0 if false
 */
int str_ends_with(const char *str, const char *suffix);

#endif /* STR_UTILS_H */
