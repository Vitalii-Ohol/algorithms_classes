#include <stdio.h>
#include <stdint.h>


int main()
{
	uint_fast32_t count = 0;
	uint_fast32_t base = 0;
	uint_fast64_t sum = 0;
	uint_fast64_t numlen = 0;

	register int c = getc_unlocked(stdin);
	for( ; ((c<48 || c>57)); c = getc_unlocked(stdin) );
	for( ;c>47 && c<58; c = getc_unlocked(stdin) ) {
		count = (count << 1) + (count << 3) + c - 48;
		++numlen;
	}

	c = getc_unlocked(stdin);
	for( ; ((c<48 || c>57)); c = getc_unlocked(stdin) );
	for( ;c>47 && c<58; c = getc_unlocked(stdin) ) {
		base = (base << 1) + (base << 3) + c - 48;
		++numlen;
	}

	while(count) {
		--count;
		uint_fast32_t num = 0;
		c = getc_unlocked(stdin);
		for( ; ((c<48 || c>57)); c = getc_unlocked(stdin) );
		for( ;c>47 && c<58; c = getc_unlocked(stdin) ) {
			num = (num << 1) + (num << 3) + c - 48;
			++numlen;
		}
		sum = sum + num;
//        __asm__ (
//            "add %[in], %[out]"
//            : [out] "+m"(sum)
//            : [in] "ir"(num)//, "[out]" "m"(*dest)
//        );
	}

	uint_fast64_t t = 1;
	if(base != 1) {
		while (sum >= base) {
			sum = sum / base;
			++t;
		}
	} else {
		t = sum;
	}
	fprintf(stdout, "%llu\n%llu", t, numlen);
	return 0;
}
