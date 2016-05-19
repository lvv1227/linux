

unsigned strln(const char *str) {
     unsigned int len=0;
     while(*str!='\0'){
         str++;
         len++;
     }
     return len;
}

int stringStat(const char *string, int multiplier, int *count){
	*count = *count+1;
	return strln(string)*multiplier;	
}
