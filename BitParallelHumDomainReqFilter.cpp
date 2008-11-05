/**
 * @author Stefan Partusch
 * @copyright (c) 2008 Stefan Partusch
 */

#include "BitParallelHumDomainReqFilter.hpp"
#include <iostream>
#include <string>

BitParallelHumDomainReqFilter::BitParallelHumDomainReqFilter() {
	const char consonants[] = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";

	for(int i = 0; i < HUMAN_REQUEST_BIT_MASK_SIZE; i++) {
		if((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z')) {
			humanReqBitMask[i] = CHARACTER_STATES;

			for(int j=0; consonants[j]; j++) {
				if(i == consonants[j]) {
					humanReqBitMask[i] |= CONSONANTS_STATES;
					break;
				}
			}

			if(i >= 'A' && i <= 'Z') {
				humanReqBitMask[i] |= UPPERCASE_STATE;
			}
		} else if(i >= '0' && i<= '9') {
			humanReqBitMask[i] = DIGIT_STATES;
		} else if(i == '.') {
			humanReqBitMask[i] = DOT_STATE;
		} else {
			humanReqBitMask[i] = CHARACTER_STATES;
		}
	}
}

bool BitParallelHumDomainReqFilter::containsHumanDomainRequest(const std::string line) const {
	const char* in = line.c_str();
	int states = 0;
	int dots = 0;
	int charDigitAlts = 0;
	int characters = 0;
	int upperCases = 0;

	for(; *in; in++) {
		states = ((states << 1) | INITIAL_STATES) & humanReqBitMask[(int) *in];

		if(states & ANY_CHAR_FIN_STATE) {
			// some character other than dots and digits
			characters++;
		}

		if(states & UPPERCASE_FIN_STATE) {
			upperCases++;
			if(upperCases == MAX_NUM_UPPERCASE_LETTERS) {
				// too many uppercase letters
				return false;
			}
		}

		if(states & CHARDIGIT_FIN_STATES) {
			charDigitAlts++;
			if(charDigitAlts == MAX_CHAR_DIGIT_ALTERNATIONS) {
				// too many changes from letters to digits and vice versa
				return false;
			}
		} else if(states & DOT_FIN_STATE) {
			dots++;
			if(dots == MAX_NUM_DOTS) {
				// too many dots
				return false;
			}
		} else if(states & CONSONANTS_FIN_STATE) {
			// sixth consonant in a row
			return false;
		}
	}

	if(!characters | (characters < dots)) {
		// no characters at all or more dots than characters
		return false;
	}

	return true;
}

void BitParallelHumDomainReqFilter::processHumanDomainRequest(const std::string domainLine) const {
	std::cout << domainLine << std::endl;
}

void BitParallelHumDomainReqFilter::filter(std::istream &in) const {
	std::string line;

	while(in) {
		std::getline(in, line);
		if(containsHumanDomainRequest(line)) {
			processHumanDomainRequest(line);
		}
	}
}

