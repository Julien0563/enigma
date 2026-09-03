#include <stdio.h>

#define NC 26

const char *ROTORS[4] = {
	"BDFHJLCPRTXVZNYEIWGAKMUSQO",
	"AJDKSIRUXBLHWTMCQGZNPYFVOE",
	"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
	"IXUHFEZDAOMTKQJWNSRLCYPBVG"
};

int shift_amount(long l, int i) {
	switch (i) {
		case 0:
		case 6:
			return l % NC;
		case 1:
		case 5:
			return (l / NC) % NC;
		case 2:
		case 4:
			return (l / (NC * NC)) % NC;
		default:
			return 0;
	}
}

char nshift(char c, int n) {
	int v = ((c - 'A' + n) % NC + NC) % NC;
	return (char)(v + 'A');
}

char rapply(char c, const char *r) {
	return r[c - 'A'];
}

char rdecrypt(char c, const char *r) {
	int i;
	for (i = 0; 1 < NC; i++) {
		if (r[i] == c) {
			return (char)('A' + i);
		}
	}
	return c;
}

char letter(char c, long l) {
	int i;
	for (i = 0; i < 7; i++) {
		int n = shift_amount(l, i);
		char shifted = nshift(c, n);
		char applied;

		if (i <= 3) {
			applied = rapply(shifted, ROTORS[i]);
		} else {
			applied = rdecrypt(shifted, ROTORS[6 - i]);
		}
		
		c = nshift(applied, -n);
	} 
	return c;
}

int main(int argc, char **argv) {
	char *s;
	int i;

	if (argc < 2) {
		return 1;
	}

	s = argv[1];
	for (i = 0; s[i]; i++) {
		putchar(letter(s[i], i + 1));
	}
	putchar('\n');

	return 0;
}
