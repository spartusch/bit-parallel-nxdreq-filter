Rules
-----

This is a simple bit-parallel filter that applies several rules to determine whether DNS requests from NXDOMAIN logs were entered manually by humans or not. Requests are considered manual if all of the following rules apply:

- doesn't contain more than three uppercase letters
- has not more than three alternations between digits and characters
- has not more than three subdomains in it
- does not contain more than five consonants in a row
- contains letters

These rules have not been validated.

Bit-Parallel Implementation
---------------------------

The filter encodes a deterministic finite-state automaton with twelve states/transitions in an integer. Bit masks are computed in advance for all possible characters and are applied for each input character. Stepping through the automaton is very efficient since all transitions are computed in parallel by fetching the relevant bit masks in linear time and by applying simple bit operations. Please see "Flexible Pattern Matching in Strings" by Gonzalo Navarro, Mathieu Raffinot for the general idea (and a lot of other interesting algorithms.)

Bibliography
------------

G. Navarro, M. Raffinot. Flexible Pattern Matching in Strings. Cambridge University Press, 2007.
