#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;



// Loads words and leaves only 5-letter words with no repititions,
// also leaving only single world among anagrams.
vector<string> LoadWords(std::string filename) {
	vector<string> words;
	ifstream file(filename);
	vector<bool> seen(26*26*26*26*26);
	while (!file.eof()) {
		string word;
		file >> word;
		if (word.length() != 5) continue;
		string tmp = word;
		sort(tmp.begin(), tmp.end());
		bool bad_word = false;
		for (int i = 0; i < 4; ++i) {
			if (tmp[i] == tmp[i+1]) {
				bad_word = true;
				break;
			}
		}
		if (bad_word) continue;
		int hash = 0;
		for (int i = 0; i < 5; ++i) {
			hash = hash*26 + tmp[i] - 'a';
		}
		if (seen[hash]) continue;
		seen[hash] = true;
		words.push_back(word);
	}
	return words;
}

void OutputAllSets(const vector<vector<bool>> &can_construct,
					const vector<string> &words,
					const vector<int> &masks,
					vector<int> &result,
					int mask,
					int start_from) {
	if (result.size() == 5) {
		for (int i = 0; i < 5; ++i) {
			cout << words[result[i]] << ' ';
		}
		cout << "\n";
		return;
	}
	for (int cur_word = start_from; cur_word < (int)words.size(); ++cur_word) {
		if (((mask & masks[cur_word]) == masks[cur_word]) && (result.size() == 4 || can_construct[3-result.size()][mask ^ masks[cur_word]])) {
			result.push_back(cur_word);
			OutputAllSets(can_construct, words, masks, result, mask ^ masks[cur_word], cur_word + 1);
			result.pop_back();
		}
	}
}


void Solve(const vector<string> &words) {
	vector<vector<bool>> can_construct(5, vector<bool>(1 << 26));
	vector<int> masks(words.size());
	for (int i = 0 ; i < (int)words.size(); ++i) {
		int mask = 0;
		for (auto c: words[i]) {
			mask |= 1 << (c - 'a');
		}
		masks[i] = mask;
		can_construct[0][mask] = true;
	}
	for (int cnt = 0; cnt < 4; ++cnt) {
		for (int mask = 0; mask < (1 << 26); ++mask) {
			if (!can_construct[cnt][mask]) continue;
			for (int i = 0; i < (int)words.size(); ++i) {
				if ((masks[i] & mask) == 0) {
					can_construct[cnt+1][masks[i] | mask] = true;
				}
			}
		}
	}

	cerr << "DP done\n";

	vector<int> result;
	for (int mask = 0; mask < (1 << 26); ++mask) {
		if (can_construct[4][mask]) {
			OutputAllSets(can_construct, words, masks, result, mask, 0);
		}
	}
}

int main() {
	vector<string> words = LoadWords("words_alpha.txt");
	Solve(words);
}