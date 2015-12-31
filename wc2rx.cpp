#include "wc2rx.h"
#include <string>
#include <cctype> 

/*
At this stage, this takes a possible regex symbol and escapes it...to make it a non regex symbol.
*/
 
std::string wc2rx(const std::string &wc_str, const bool enableEscaping, bool _isEscaping)
{

	const int wclen = wc_str.length();
	if (wc_str == "@|")
		int a = 9;
	std::string rx;
	int i = 0;
	bool	isEscaping = _isEscaping;
	const char *wc = wc_str.c_str();

	while (i < wclen) {
		const char c = wc[i++];
		switch (c) {
		case '\\':
			if (enableEscaping) {
				if (isEscaping) {
					rx += std::string("\\\\");
				} // we insert the \\ later if necessary
				if (i == wclen) { // the end
					rx += std::string("\\\\");
				}
			}
			else {
				rx += std::string("\\\\");
			}
			isEscaping = true;
			break;
		case '*':
			if (isEscaping) {
				rx += std::string("\\*");
				isEscaping = false;
			}
			else {
				rx += std::string(".*");
			}
			break;
		case '?':
			if (isEscaping) {
				rx += std::string("\\?");
				isEscaping = false;
			}
			else {
				rx += char('.');
			}

			break;
		case '@':
			//	if (isEscaping) {
			isEscaping = false;
			//		rx += std::string("\\\\");
			//	}
			rx += char('\\');
			rx += c;
			break;
		case '|':
			//	if (isEscaping) {
			isEscaping = false;
			//		rx += std::string("\\\\");
			//	}
			rx += char('\\');
			rx += c;
		  break;
		case '+':
			rx += char('\\');
			rx += c;
			break;
		case '$':
		case '(':
		case ')':
		case '^':
		case '{':
		case '}':
			if (isEscaping) {
	  		isEscaping = false;
				rx += std::string("\\\\");
			}
			rx += char('\\');
			rx += c;
			break;
		case '!': // to run rosetta
		case '-': // to run rosetta
		case '_': // to run rosetta
		case ',': // to run rosetta
		case '>': // to run rosetta
		case '.': // to run rosetta
			rx += c;
			break;
		case '[':
			if (isEscaping) {
				isEscaping = false;
				rx += std::string("\\[");
			}
			else {
				rx += c;
				if (wc[i] == char('^'))
					rx += wc[i++];
				if (i < wclen) {
					if (rx[i] == char(']'))
						rx += wc[i++];
					while (i < wclen && wc[i] != char(']')) {
						if (wc[i] == char('\\'))
							rx += char('\\');
						rx += wc[i++];
					}
				}
			}
			break;

		case ']':
			if (isEscaping){
				isEscaping = false;
				rx += std::string("\\");
			}
			rx += c;
			break;

		default:
			std::locale loc;
			if (std::isalnum(c) != 0) // rosetta
			{
				rx += c;

			}
			else if (isEscaping){
				isEscaping = false;
				rx += std::string("\\\\");
			}
			else rx += c;
			break;
		}
	}
	return rx;
}