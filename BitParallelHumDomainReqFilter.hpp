/**
 * @author Stefan Partusch
 * @copyright (c) 2008 Stefan Partusch
 */

#ifndef SP_BITPARALLELHUMDOMAINREQFILTER
#define SP_BITPARALLELHUMDOMAINREQFILTER

#include <iostream>

class BitParallelHumDomainReqFilter {
	private:
		static const int HUMAN_REQUEST_BIT_MASK_SIZE = 0xFF;
		static const int MAX_NUM_DOTS = 4;
		static const int MAX_NUM_UPPERCASE_LETTERS = 4;
		static const int MAX_CHAR_DIGIT_ALTERNATIONS = 4;

		static const int INITIAL_STATES       = 0b100000110101;

		static const int CHARACTER_STATES     = 0b000000001001;
		static const int DIGIT_STATES         = 0b000000000110;
		static const int DOT_STATE            = 0b000000010000;
		static const int CONSONANTS_STATES    = 0b011111100000;
		static const int UPPERCASE_STATE      = 0b100000000000;

		static const int ANY_CHAR_FIN_STATE   = 0b000000000001;
		static const int CHARDIGIT_FIN_STATES = 0b000000001010;
		static const int DOT_FIN_STATE        = 0b000000010000;
		static const int CONSONANTS_FIN_STATE = 0b010000000000;
		static const int UPPERCASE_FIN_STATE  = 0b100000000000;

		int humanReqBitMask[HUMAN_REQUEST_BIT_MASK_SIZE];

	protected:
		bool containsHumanDomainRequest(const std::string line) const;
		void processHumanDomainRequest(const std::string domainLine) const;

	public:
		BitParallelHumDomainReqFilter();
		void filter(std::istream &in) const;
};

#endif
