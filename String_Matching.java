package strings;

import java.util.Scanner;

// Knuth-Morris-Pratt (KMP) Substring search algorithm

class String_Matching {
	static int[] prefix;

	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextLine()) {
			// Match pattern to expression
			String pattern = sc.nextLine();
			String expression = sc.nextLine();
			KMP(pattern, expression);
			System.out.println();
		}
	}

	// KMP skips comparisons already made.
	static void KMP(String pattern, String expression) {
		int patternLength = pattern.length(); //k
		int expressionLength = expression.length(); //n

		// Mapping array (lps)
		prefix = new int[patternLength];
		
		longestPrefixSuffix(pattern);
		
		int patternIdx = 0;
		int expressionIdx = 0;
		
		// Algorithm very similar to KMP in lecture, 0:49min
		while (expressionIdx < expressionLength) {
			if (pattern.charAt(patternIdx) == expression.charAt(expressionIdx)) {
				patternIdx++;  
				expressionIdx++;
			}

			if (patternIdx == patternLength) {
				System.out.print((expressionIdx - patternIdx + " "));
				patternIdx = prefix[patternIdx - 1];
			}

			else if (expressionIdx < expressionLength
					&& pattern.charAt(patternIdx) != expression.charAt(expressionIdx)) {
				if (patternIdx != 0)
					patternIdx = prefix[patternIdx - 1];
				else
					expressionIdx += 1;
			}
		}
	}

	//From lecture: Create mapping array (lps). Lps is the longest proper prefix that is also a suffix in pattern[:1]
	static void longestPrefixSuffix(String pattern) {
		//Complexity: O(n)
		int n = 0;
		int k = pattern.length();

		int idx = 1;
		prefix[0] = 0;

		while (idx < k) {
			if (pattern.charAt(idx) == pattern.charAt(n)) {
				n++;
				prefix[idx] = n;
				idx += 1;
			} else {
				if (n != 0) {
					n = prefix[n - 1];
				} else {
					prefix[idx] = 0;
					idx += 1;
				}
			}
		}
		
		/*
		 * for(int i = 0; i < prefix.length; i++) { System.out.println(prefix[i]); }
		 */
		
		return;
	}

}