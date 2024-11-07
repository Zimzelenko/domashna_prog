#include <bits/stdc++.h>
using namespace std;

class String {
	char * chars;
	unsigned int length;

public:
	String() {
		chars = new char[1];
		chars[0] = '\0';
		length = 0;
	}

	String(char *chars, unsigned int length) {
		this->chars = new char[length + 1];
		strncpy(this->chars, chars, length);
		this->chars[length] = '\0';
		this->length = length;
	}

	~String() {
		if (chars) {
			delete[] chars;
		}
	}

	String &operator=(const String &other) {
		if (this != &other) {
			delete[] chars;
			length = other.length;
			chars = new char[length + 1];
			strcpy(chars, other.chars);
		}
		return *this;
	}

	String(const String &other) {
		length = other.length;
		chars = new char[length + 1];
		strcpy(chars, other.chars);
	}

	void constructLPS(const String &subStr, vector<int> &lps) {
		int len = 0;
		lps[0] = 0;
		int i = 1;
		while (i < subStr.length) {
			if (subStr.chars[i] == subStr.chars[len]) {
				len++;
				lps[i] = len;
				i++;
			} else {
				if (len != 0)
					len = lps[len - 1];
				else {
					lps[i] = 0;
					i++;
				}
			}
		}
	}
	void constructReverseLPS(const String & subStr, vector<int> & r_lps) {
		int len = 0;
		r_lps[subStr.length - 1] = 0;
		int i = subStr.length - 2;
		while (i >= 0) {
			if (subStr.chars[i] == subStr.chars[subStr.length - len - 1]) {
				len++;
				r_lps[i] = len;
				i--;
			} else {
				if (len != 0)
					len = r_lps[subStr.length - len];
				else {
					r_lps[i] = 0;
					i--;
				}
			}
		}
	}
	// Implement KMP on the whole string
	vector<int> findAllSubStr(const String &subStr) {
		int n = this->length;
		int m = subStr.length;
		vector<int> lps(m);
		vector<int> res;
		constructLPS(subStr, lps);
		int i = 0, j = 0;
		while (i < n) {
			if (this->chars[i] == subStr.chars[j]) {
				i++;
				j++;
				if (j == m) {
					res.push_back(i - j);
					j = lps[j - 1];
				}
			} else {
				if (j != 0)
					j = lps[j - 1];
				else
					i++;
			}
		}
		return res;
	}

	// Implement KMP until the first match
	int findFirstSubStr(const String & subStr) {
		int n = this->length;
		int m = subStr.length;
		vector<int> lps(m);
		vector<int> res;
		constructLPS(subStr, lps);
		int i = 0, j = 0;
		while (i < n && res.size() < 1) {
			if (this->chars[i] == subStr.chars[j]) {
				i++;
				j++;
				if (j == m) {
					return i - j;
				}
			} else {
				if (j != 0)
					j = lps[j - 1];
				else
					i++;
			}
		}
		return -1;
	}

	// Implement KMP in reverse (search from the end of both strings).
	// The lookup table should be done from last character
	int findLastSubStr(const String & subStr) {
		int n = this->length;
		int m = subStr.length;
		vector<int> r_lps(m);
		constructReverseLPS(subStr, r_lps);
		int i = n - 1, j = m - 1;
		while (i >= 0) {
			if (this->chars[i] == subStr.chars[j]) {
				i--;
				j--;
				if (j < 0) {
					return i + 1;
				}
			} else {
				if (j != m - 1)
					j = m - r_lps[j] - 1;
				else
					i--;
			}
		}
		return -1;
	}

	vector<int> findAllSubStrReverse(const String & subStr) {
		int n = this->length;
		int m = subStr.length;
		vector<int> r_lps(m);
		constructReverseLPS(subStr, r_lps);
		vector<int> result;
		int i = n - 1, j = m - 1;
		while (i >= 0) {
			if (this->chars[i] == subStr.chars[j]) {
				i--;
				j--;
				if (j < 0) {
					result.push_back(i + 1);
					j = r_lps[j];
				}
			} else {
				if (j != m - 1)
					j = m - r_lps[j] - 1;
				else
					i--;
			}
		}
		return result;
	}
};
int main()
{
	unsigned int length, p_length;
	//Enter string length
	cin >> length;
	char * s = new char[length];
	//Enter the string
	for (int i = 0; i < length; i++) {
		cin >> s[i];
	}

	//Enter pattern length
	cin >> p_length;
	char * p = new char[p_length];
	//Enter the pattern
	for (int i = 0; i < p_length; i++) {
		cin >> p[i];
	}

	String str(s, length);
	String pat(p, p_length);
	vector<int> print = str.findAllSubStr(pat);

	for (int i : print) {
		cout << i << " ";
	}
	cout << endl;

	cout << str.findFirstSubStr(pat);

	cout << endl;

	cout << str.findLastSubStr(pat);

    cout << endl;

	vector<int> print_reverse = str.findAllSubStrReverse(pat);

	for (int i : print_reverse) {
		cout << i << " ";
	}

	delete[] s;
	delete[] p;

	return 0;
}