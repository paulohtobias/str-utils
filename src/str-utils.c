#include "str-utils.h"

char *str_from_file(const char *file_name){
	char *str = NULL;
    FILE *in = fopen(file_name, "r");
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
    fclose(in);

    return str;
}

char *str_replace(const char *orig, const char *rep, const char *with){
	char *result; // the return string
    const char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

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
		char c1 = str[i], c2 = suffix[i - (len_str - len_suffix)];
		if(str[i] != suffix[i - (len_str - len_suffix)]){
			return 0;
		}
	}
	
	return 1;
}
