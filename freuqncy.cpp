#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <set>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

char alphabet (char x) {
	if (x >= 'a' && x <= 'z') {
		return x - 'a' + 'A';
	} else if (x >= 'A' && x <= 'Z') {
		return x;
	}
	return 0;
}

set <pair<int, char> > compute_frequency (char* text, size_t s_len) {
	set <pair<int, char> > ret_set;
	map <char, int> freq_map;

	for (size_t i = 0; i != s_len; i++) {
		if (!alphabet(text[i])) {
			continue;
		}
		if (!alphabet(text[i])) {
			continue;
		}
		if (freq_map.find(alphabet(text[i])) == freq_map.end()) {
			freq_map[alphabet(text[i])] = 0;
		}
		freq_map[alphabet(text[i])] ++;
	}

	map <char, int> :: iterator it;

	for (it = freq_map.begin(); it != freq_map.end(); it++) {
		ret_set.insert (pair<int, char>(it->second, it->first));
	}

	return ret_set;
}

void substitute (char* text, size_t s_len, char* sub_map) {
	for (int i=0;i<s_len;i++) {
		if (!alphabet(text[i])) {
			printf ("%c", text[i]);
		} else {
			printf ("%c", sub_map[alphabet(text[i])-'A']);
		}
	}
	printf ("\n");
}

int main (int argc, char* argv[]) {

	FILE* in_file = fopen (argv[1], "rb");
	if (in_file == NULL) {
		cerr << "File Not Found\n";
		return 0;
	}

	fseek (in_file, 0, SEEK_END);
	size_t s_len = ftell (in_file);
	rewind (in_file);

	char* text = (char*) malloc (sizeof(char)*s_len);
	if (text == NULL) {
		cerr << "Error allocating memory\n";
		return 0;
	}

	size_t read_cnt = fread(text, 1, s_len, in_file);
	if (read_cnt != s_len) {
		cerr << "Error Reading File\n";
		return 0;
	}

	set <pair<int, char> > freq_set = compute_frequency (text, s_len);
	set <pair<int, char> > :: iterator it;

	for (it = freq_set.begin(); it != freq_set.end(); it++) {
		printf ("(%d, %c)\n", it->first, it->second);
	}
//char sub_map[] = "XTWDVQZLSONBAUGHKEPYRCIFMJ";
	char sub_map[] = "LMNOPQRSTUVWXYZABCDEFGHIJK";
	substitute (text, s_len, sub_map);

	return 0;
}