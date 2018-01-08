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
    char *ins;    // the next insert point
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
	while(isdigit(str[*index])){
		(*index)++;
	}
	
	return atoi(str);
}

int strcmpn(const char *s1, const char *s2){
	//Getting the lengths of s1 and s2
    int l1 = strlen(s1);
    int l2 = strlen(s2);
	
	//Used to compare the chars.
	int c1, c2;

    //Variables to store the numbers inside the strings
    char n1s[32], n2s[32];
    int n1 = 0, n2 = 0;

    int i1, i2, j, k;
    for(i1 = 0, i2 = 0; i1 < l1 && i2 < l2; i1++, i2++){
        if(isdigit(s1[i1]) && isdigit(s2[i2])){

			//Getting the number inside s1.
            for(j = i1; j < l1 && isdigit(s1[j]); j++){
                n1s[j-i1] = s1[j];
            }
            n1s[j-i1] = '\0';
            n1 = atoi(n1s);

			//Getting the number inside s2.
            for(k=i2; k<l2 && isdigit(s2[k]); k++){
                n2s[k-i2] = s2[k];
            }
            n2s[k-i2] = '\0';
            n2 = atoi(n2s);

            if(n1 != n2){
                return n1 - n2;
			}

            i1=j-1;
            i2=k-1;
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
